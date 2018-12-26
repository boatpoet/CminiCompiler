#include "Syntax.h"

extern vector<vector<SymbolTable>> synbl;       //�������ű�����������Ҫ��������
int curSynblLev = 0;						 //��ǰ���ڷ��ű�Ĳ��
int preSynblLev = -1;						 //ǰһ����ű�Ĳ��

Syntax::Syntax() {
	quat.open("quat.dat");
	TapelIndex = 4;
	Action_map["PUSH"] = _push;
	Action_map["POP"] = _pop;
	Action_map["LABER"] = _laber;
	Action_map["GOTO"] = _goto;
	Action_map["ASSI"] = _assi;
	Action_map["GEQ"] = _geq;
	Action_map["GEQ_UNARY"] = _geq_unary;
	Action_map["RELATION"] = _relation;
	Action_map["IF"] = _if;
	Action_map["ELSE"] = _else;
	Action_map["WHILE"] = _while;
	Action_map["DO"] = _do;
	Action_map["LOGIC"] = _logic;
	Action_map["SCOPEINIT"] = _scope_init;
	Action_map["PARAM"] = _param;
	Action_map["CALL"] = _call;
	Action_map["END"] = _end;
	Action_map["RETURN"] = _return;
	Action_map["FOR"] = _for;
	Action_map["FORINC"] = _for_inc;
	Action_map["FORSECPRE"] = _for_sec_pre;
	Action_map["FORSECPST"] = _for_sec_post;
	Action_map["FORTHDPRE"] = _for_third_pre;
	Action_map["FORTHDPST"] = _for_third_post;
	Action_map["DOWHILE"] = _do_while;
	Action_map["DOWHCMP"] = _do_while_cmp;
	Action_map["ENDDOWH"] = _end_dowh;
	Action_map["SCANF"] = _cin;
	Action_map["PRINT"] = _cout;
	Action_map["INITDECL"] = _init_decl;
	Action_map["INITARR"] = _init_arr;
	Action_map["GETFUNCNM"] = _get_func_name;
	Action_map["STRUCTINIT"] = _struct_scopeinit;

	Tapel[0].Tval = TypeTable::_int;
	Tapel[0].Tpoint = -1;
	Tapel[1].Tval = TypeTable::_float;
	Tapel[1].Tpoint = -1;
	Tapel[2].Tval = TypeTable::_double;
	Tapel[2].Tpoint = -1;
	Tapel[3].Tval = TypeTable::_long;
	Tapel[3].Tpoint = -1;
	Tapel[4].Tval = TypeTable::_short;
	Tapel[4].Tpoint = -1;
	Tapel[5].Tval = TypeTable::_char;
	Tapel[5].Tpoint = -1;
	SymbolTable tmpsymb; //��ʼ��ȫ�ַ��ű�
	tmpsymb.prelev = -1;
	vector<SymbolTable> tmpvec;
	tmpvec.push_back(tmpsymb);
	synbl.push_back(tmpvec);
}
//return pair<typeId, sizeof(dataType)> 
pair<int, int> Syntax::getTypeCode(string type) //�������뼰������ռ�ڴ浥Ԫ�ĳ���
{
	if (type == "int") return make_pair(0, 2);
	else if (type == "float") return make_pair(1, 2);
	else if (type == "double") return make_pair(2, 4);
	else if (type == "long") return make_pair(3, 4);
	else if (type == "short") return make_pair(4, 1);
	else if (type == "char") return make_pair(5, 2);
	else if (type == "void") return make_pair(-1, 0); //��void�����������
	/*else {
	//��������
	Tapel[TapelIndex++].Tval =
	}*/
}

bool Syntax::isExistInSynbl(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		vector<SymbolTable>::iterator it = synbl[index].begin(), stor_it = it;
		for (; it != synbl[index].end(); it++) {
			if (it->name == id) {
				return true;
			}
		}
		if (it == synbl[index].end() || synbl[index][0].prelev != -1) {
			//��ǰ������ķ��ű���δ�ҵ��ñ�ʶ�����Ҹ��������ȫ��������
			return isExistInSynbl(id, synbl[index][0].prelev);
		}
		else if (it == synbl[index].end() || synbl[index][0].prelev == -1) {
			return false;
		}
	}
	else return false;
}

int Syntax::getOffset(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		vector<SymbolTable>::iterator it = synbl[index].begin(), stor_it = it;
		for (; it != synbl[index].end(); it++) {
			if (it->name == id) {
				return it->offset;
			}
		}
		if (it == synbl[index].end() || synbl[index][0].prelev != -1) {
			//��ǰ������ķ��ű���δ�ҵ��ñ�ʶ�����Ҹ��������ȫ��������
			return getOffset(id, synbl[index][0].prelev);
		}
		else if (it == synbl[index].end() || synbl[index][0].prelev == -1) {
			return -1;
		}
	}
	else return -1;
}

bool isExistInCurDomain(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		for (vector<SymbolTable>::iterator it = synbl[index].begin(); it != synbl[index].end(); it++) {
			if (it->name == id) {
				return true;
			}
		}
		return false;
	}
}

int token_ptr = 0; //token����
static int qtmpID = 0;
string tmpstr;
int paramId = 1; //��ǵڼ�������
pair<string, int> tmp, funcName;
extern int off; //�ݴ�ƫ����
bool isElif = false;
void Syntax::Call(string Action, int TokenIndex, string curstr) {
	vector<SymbolTable> tmpSynbl; //��ʱ�����ű�
	SymbolTable tmpNode; //��ʱ�����ű���
	stack<pair<string, int>> tmpStack;
	if (!quat) {
		cout << "��Ԫʽ�ļ��򿪳���" << endl;
		exit(1);
	}
	//cout << "*****************����ջ����SEM***********************" << endl;
	switch (Action_map[Action])
	{
	case Action_id::_push: SEM.push(make_pair(curstr, TokenIndex));
		//for test
		//cout << curstr << "ѹ������ջSEM" << endl;
		//for test
		break;
	case Action_id::_pop:
		while (!SEM.empty()) {
			if (tokenSeq[SEM.top().second].type == _constnum)
			{	//��ֵ��� stack<pair<string, int>> SEM;
				string constnum = SEM.top().first; //��¼�¸ó���
				SEM.pop(); //ֵ��ջ
				token_ptr = SEM.top().second; //id��Token����
				int i;
				for (i = 0; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
					//���ñ����Ƿ��Ѿ������
					if (synbl[curSynblLev][i].name == identifier_table[tokenSeq[SEM.top().second].id].name) {
						//�ظ�����
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2086: ��int " << identifier_table[tokenSeq[SEM.top().second].id].name << "��: �ض���." << endl;
						//SEM.pop();
						exit(1); //�ض���ֱ��ֹͣ����
						//break;
					}
				}
				//if (!synbl.empty() && i < synbl[curSynblLev].size()) continue; //�����ض���
				tmpNode.name = SEM.top().first;
				tmpNode.prelev = preSynblLev;
				//cout << "tmpNode.prelev = " << tmpNode.prelev << endl;//for test
				SEM.pop(); //id��ջ
				stack<pair<string, int>> tmpSEM;
				while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
					tmpSEM.push(SEM.top());
					SEM.pop();
				} //���ҹ��˵�ͬһ�д���ǰ��Ķ��������
				string tmptype = "";
				while (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					//����ű��Type���������������ӵ����ͱ�
					tmptype += (SEM.top().first + " ");
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				tmptype = tmptype.substr(0, tmptype.size() - 1); //ȥ�������Ŀո�
				tmpNode.typ = getTypeCode(tmptype).first; //��д���ű��TYP������ 
				//identifier_table[synbl_ptr].typ = getTypeCode(tmptype);   
				if (tmpNode.typ == -1) {
					//void���ͱ����ڶ��������������
					cout << "Line " << tokenSeq[token_ptr].row << ": " << endl;
					cout << "error C2182: ��" << SEM.top().first << "��: �Ƿ�ʹ�á�void������" << endl;
					exit(1);
				}
				tmpNode.offset = off;
				off += getTypeCode(tmptype).second;
				//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
				if (!synbl.empty() && curSynblLev < synbl.size()) {
					synbl[curSynblLev].push_back(tmpNode); //�����ű��Ѿ����ڵ����
				}
				//if (curSynblLev >= synbl.size()) {
				else {
					//��ǰ������״���д���������ű����ڵ����
					tmpSynbl.push_back(tmpNode); //��ǰ�����뵥���ű���
					synbl.push_back(tmpSynbl);
					//cout << "�����½ڵ�" << synbl.size() - 1 << ": prelev = " << tmpNode.prelev << endl;//for test
				}
				quat << "= " << constnum << " # " << tmpNode.name << endl; //������Ԫʽ
				while (!tmpSEM.empty()) { //�ݴ�����ԭ����ջ��
					SEM.push(tmpSEM.top());
					tmpSEM.pop();
				}
			}
			else if (tokenSeq[SEM.top().second].type == _identifier) {
				//��������� int b;
				int i;
				for (i = 0; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
					//���ñ����Ƿ��Ѿ������
					if (synbl[curSynblLev][i].name == SEM.top().first) {
						//�ظ�����
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2086: ��int " << SEM.top().first << "��: �ض���." << endl;
						//SEM.pop();
						//break;
						exit(1); //�ض���ֱ��ֹͣ����
					}
				}
				//if (!synbl.empty() && i < synbl[curSynblLev].size()) continue; //�����ض���
				tmpNode.name = SEM.top().first;
				tmpNode.prelev = preSynblLev;
				//cout << "tmpNode.prelev = " << tmpNode.prelev << endl; //for test
				//synbl_ptr = tokenSeq[SEM.top().second].id;
				token_ptr = SEM.top().second;
				SEM.pop(); //id��ջ
				stack<pair<string, int>> tmpSEM;
				while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				string tmptype = "";
				while (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					//����ű��Type���������������ӵ����ͱ�
					tmptype += (SEM.top().first + " ");
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				tmptype = tmptype.substr(0, tmptype.size() - 1); //ȥ�������Ŀո�
				tmpNode.typ = getTypeCode(tmptype).first; //��д���ű��TYP������
														  //identifier_table[synbl_ptr].typ = getTypeCode(tmptype);   //��д���ű��TYP������
				if (tmpNode.typ == -1) {
					//void���ͱ����ڶ��������������
					cout << "Line " << tokenSeq[token_ptr].row << ": " << endl;
					cout << "error C2182: ��" << tmpNode.name << "��: �Ƿ�ʹ�á�void������." << endl;
					exit(1);
				}

				//for test
				//cout << tmpNode.typ << "������ű�TYP��, " << endl;
				//for test
				tmpNode.offset = off; //��¼֮ǰ��ƫ����
				//cout << "��ǰƫ����Ϊ��" << tmpNode.offset << endl; //for test
				off += getTypeCode(tmptype).second; //���µ�ǰƫ����
				//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
				if (!synbl.empty() && curSynblLev < synbl.size()) {
					synbl[curSynblLev].push_back(tmpNode); //�����ű��Ѿ����ڵ����
				//	cout << endl << tmpNode.name << "����synbl[" << curSynblLev << "]" << endl; //for test
				}
				//if (curSynblLev >= synbl.size()) {
				else {
					//��ǰ������״���д���������ű����ڵ����
					tmpSynbl.push_back(tmpNode); //��ǰ�����뵥���ű���
					synbl.push_back(tmpSynbl);
				//	cout << "�����ܱ��½ڵ�" << synbl.size() - 1 << ": " << tmpNode.name << "����";
				//	cout << ", prevel = " << tmpNode.prelev << endl;//for test
				}

				while (!tmpSEM.empty()) { //�ݴ�����ԭ����ջ��
					SEM.push(tmpSEM.top());
					tmpSEM.pop();
				}
			}
			else SEM.pop();
		}
		break;
	case Action_id::_laber: quat << "label # # " << SEM.top().first << endl;
		SEM.pop();
		break;
	case Action_id::_goto: quat << "gt # # " << curstr << endl;
		break;
	case Action_id::_assi:
		if (!SEM.empty()) {
			tmp = SEM.top();
			SEM.pop(); //number is out!
		/*	if (tmp.first == "1")
				cout << "stop";*/
			if (tmp.first == "return_val") {
				SEM.pop(); //pop =
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
					quat << "mov " << SEM.top().first << " # DX" << endl;
				}
			}
			else if (!SEM.empty() && SEM.top().first == "=") {
				//quat << SEM.top().first << " " << tmp.first << " # ";
				SEM.pop(); //= is out
				//cout << "curSynblLev = " << curSynblLev << endl;//for test
				//cout << "preSynblLev = " << preSynblLev << endl;//for test
				/*if (SEM.top().first == "b")
					cout << "stop";*/
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum) {
					//���鸳ֵ
					pair<string, int> arroffset = SEM.top();
					SEM.pop(); //a[index]��index��ջ
					//if(stoi(arroffset.first)>=)//@@@@@@δ����û���������Խ������
					quat << "movs " << to_string(getOffset(SEM.top().first, curSynblLev) + stoi(arroffset.first)*2) << " # " << tmp.first << endl;
					//Ŀǰ֧��int�����飬int����Ϊ2
				}
				else if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || SEM.top().second == -1)) {
					quat << "= " << tmp.first << " # ";
					if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
						//���������ֵ
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2065: ��" << SEM.top().first << "��: δ�����ı�ʶ��" << endl;
						exit(1);
					}
					quat << SEM.top().first << endl;
				}
				//SEM.pop(); //delete it!
			}
			else if (!SEM.empty() && regex_match(SEM.top().first, regex("\\+=|-=|\\*=|/=|%=|&=|\\|=|^=|>>=|<<="))) {
				if (regex_match(SEM.top().first, regex("\\+=|-=|\\*=|/=|%=")))
					quat << SEM.top().first[0] << " ";
				else if (SEM.top().first == "&=") quat << "and ";
				else if (SEM.top().first == "|=") quat << "or ";
				else if (SEM.top().first == "^=") quat << "not ";
				else if (SEM.top().first == ">>=") quat << "shr ";
				else if (SEM.top().first == "<<=") quat << "shl ";
				SEM.pop();
				if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: ��" << SEM.top().first << "��: δ�����ı�ʶ��" << endl;
					exit(1);
				}
				quat << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				quat << "= qtmp" + to_string(qtmpID) << " # " << SEM.top().first << endl;
				//SEM.pop();//delete it!
				qtmpID++;
			}
			else if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier && tokenSeq[tmp.second].type == _constnum) {
				//����Ԫ�ظ�ֵ��һ������,arr_index is out in tmp, int b = a .1
				int memPos = getOffset(SEM.top().first, curSynblLev) + stoi(tmp.first) * 2;
				pair<string, int> tmpa = SEM.top();
				SEM.pop(); //a is out
				if (!SEM.empty() && SEM.top().first == "=") {
					SEM.pop();//= is out
					quat << "movs " << SEM.top().first << " # " << to_string(memPos) << endl;
				}
				else {
					SEM.push(tmpa);
					SEM.push(tmp);
				}
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_geq:
		tmpstr = SEM.top().first + " "; //cout << tmpstr << "is out!" << endl;//for test
		SEM.pop();
		quat << SEM.top().first << " ";   //cout << SEM.top().first << "is out!" << endl;//for test
		SEM.pop();
		quat << SEM.top().first << " " << tmpstr << "qtmp" + to_string(qtmpID) << endl;
		//cout << SEM.top().first << "is out!" << endl; //for test
		SEM.pop();
		SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
		qtmpID++;
		break;
	case Action_id::_geq_unary:
		if (!SEM.empty() && (SEM.top().first == "++" || SEM.top().first == "--")) {
			quat << SEM.top().first[0] << " ";
			SEM.pop();
			quat << SEM.top().first << " 1 " << "qtmp" + to_string(qtmpID) << endl;
			tmp = SEM.top();
			SEM.pop();
			quat << "= " << "qtmp" + to_string(qtmpID) << " # " << tmp.first << endl;
			SEM.push(tmp);
			qtmpID++;
		}
		else if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || SEM.top().second == -1)) {
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && (SEM.top().first == "++" || SEM.top().first == "--")) {
				quat << SEM.top().first[0] << " " << tmp.first << " 1 " << "qtmp" + to_string(qtmpID) << endl;
				quat << "= " << "qtmp" + to_string(qtmpID) << " # " << tmp.first << endl;
				SEM.pop();
				SEM.push(tmp);
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		else if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && SEM.top().first == "~") {
				quat << "not " << tmp.first << " # qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_relation:
		if (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum) {
			if (tokenSeq[SEM.top().second].type == _identifier) {
				//����Ƿ�δ����
				if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: ��" << SEM.top().first << "��: δ�����ı�ʶ��" << endl;
					exit(1);
				}
			}
			tmp = SEM.top();
			SEM.pop();
			if (SEM.top().first == "<" || SEM.top().first == ">" || SEM.top().first == "<=" || SEM.top().first == ">="
				|| SEM.top().first == "==" || SEM.top().first == "!=") {
				quat << SEM.top().first << " ";
				SEM.pop();
				if (tokenSeq[SEM.top().second].type == _identifier) {
					//����Ƿ�δ����
					if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
						//cout << "!isExistInSynbl(" << SEM.top().first << ", " << curSynblLev << ")" << endl;
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2065: ��" << SEM.top().first << "��: δ�����ı�ʶ��" << endl;
						exit(1);
					}
				}
				quat << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_if:
		if (!SEM.empty() && SEM.top().second == -1) {
			if (isElif == false) { //ֻ��if
				//cout << "------------IF------------" << endl;
				/*if (synbl.size() == 5)
					cout << "stop";*/
				preSynblLev = curSynblLev;
				//cout << "preSynblLev = " << preSynblLev << endl;//for test
				curSynblLev = synbl.size(); //���˺����������Ҫcur = pre;
				//cout << "curSynblLev = " << curSynblLev << endl;//for test
				//tmpNode.name = nullptr;
				tmpNode.prelev = preSynblLev;
				tmpNode.domainName = "if";
				tmpSynbl.push_back(tmpNode);
				synbl.push_back(tmpSynbl);
				//cout << "�����ܱ����½ڵ�" << synbl.size() - 1 << ": prelev = " << tmpNode.prelev << endl;//for test
				//cout << "------------IF------------" << endl;//for test

				quat << "if " << SEM.top().first << " # " << curSynblLev << endl;
				SEM.pop();
			}
			else {
				//else if...
				synbl[curSynblLev][0].domainName = "if";
				quat << "if " << SEM.top().first << " # " << curSynblLev << endl;
				SEM.pop();
			}
		}
		break;
	case Action_id::_else:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //���˺����������Ҫcur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "else";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);
		isElif = true;
		quat << "el # # " << curSynblLev << endl;
		break;
	case Action_id::_while:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //���˺����������Ҫcur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "while";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);

		quat << "wh # # " << curSynblLev << endl;
		break;
	case Action_id::_do:
		if (SEM.top().second == -1) {
			quat << "do " << SEM.top().first << " # #" << endl;
			SEM.pop();
		}
		break;
	case Action_id::_logic:
		if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum))
		{
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && (SEM.top().first == "&&" || SEM.top().first == "&")) {
				SEM.pop(); //&& is out!
				quat << "and " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "||" || SEM.top().first == "|")) {
				SEM.pop(); //|| is out!
				quat << "or " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "^")) {
				SEM.pop(); //^ is out!
				quat << "xor " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "<<")) {
				SEM.pop();
				quat << "shl " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == ">>")) {
				SEM.pop();
				quat << "shr " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_scope_init:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			preSynblLev = curSynblLev;   //��ǰ��α�Ϊ��һ��
			curSynblLev = synbl.size();  //��ǰ��Ϊ�����ܱ������¿��ٵ�һ��
			tmpNode.prelev = preSynblLev;//����������ָ�����¼��һ���������
			tmpNode.domainName = SEM.top().first;//��¼�������������
			tmpSynbl.push_back(tmpNode);
			synbl.push_back(tmpSynbl);   //�ڷ����ܱ���Ϊ�������򿪱ٿռ�

			tmp = SEM.top();
			SEM.pop();
			if (tokenSeq[SEM.top().second].type == _keyword) {
				quat << "func " << tmp.first << " # " << curSynblLev << endl;
				//quat << "func "<<curSynblLev<<" # " << tmp.first << endl; //generate function quat
				SEM.pop(); //data type is out of stack!
				while (!SEM.empty()) { //����һ���µ�������--��������SEMջ��֮ǰ������ȫ�����
					SEM.pop();
				}
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_get_func_name:
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
			paramId = 1;
			funcName = SEM.top();
		}
		break;
	case Action_id::_param:
		//����ʵ����Ԫʽ
		if (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum) {
			//quat << "param # # " << SEM.top().first << endl;
			int i;
			for (i = 0; i < synbl.size(); i++) {
				if (synbl[i][0].domainName == funcName.first) {
					quat << "mov " << synbl[i][paramId].offset << " # " << SEM.top().first << endl;
					break;
				}
			}
			if (i < synbl.size()) //�ҵ���
				SEM.pop();
			else {
				//û�ҵ��ú���
				cout << "Line " << tokenSeq[funcName.second].row << ": ";
				cout << "'" << funcName.first << "' was not declared in this scope" << endl;
				exit(1);
			}
			paramId++;
		}
		break;
	case Action_id::_call:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			quat << "call # # " << SEM.top().first << endl;
			SEM.pop();
			SEM.push(make_pair("return_val", -3));
		}
		break;
	case Action_id::_end:
		//cout << "---------END---------" << endl;//for test
		/*if (synbl[curSynblLev][0].domainName == "max")
			cout << "stop";*/
		quat << "end # # " << synbl[curSynblLev][0].domainName << endl;
		//cout<< "end # # " << synbl[curSynblLev][0].domainName << endl;//for test
		curSynblLev = preSynblLev;					//�ָ���ǰ������Ϊ��һ��������
		preSynblLev = synbl[preSynblLev][0].prelev; //�ָ���һ������Ϊ���ϲ�������
		//cout << "preSynblLev = " << preSynblLev << endl;//for test
		//cout << "---------END---------" << endl;//for test
		break;
	case Action_id::_return:
		if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			quat << "re " << SEM.top().first << " # #" << endl;
		}
		else if (SEM.empty()) {
			quat << "re void # #" << endl;
		}
		break;
	case Action_id::_for:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size();
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "for";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);
		quat << "for # # " << curSynblLev << endl;
		break;
	case Action_id::_for_inc:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "jmp # # inc" << endl;
		}
		break;
	case Action_id::_for_sec_pre:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "label # # cmp" << endl;
		}
		break;
	case Action_id::_for_sec_post:
		if (synbl[curSynblLev][0].domainName == "for") {
			if (SEM.top().second == -1) {
				quat << "do " << SEM.top().first << " # #" << endl;
				quat << "jmp # # end" << endl;
				quat << "jmp # # start" << endl;
			}
		}
		break;
	case Action_id::_for_third_pre:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "label # # inc" << endl;
		}
		break;
	case Action_id::_for_third_post:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "jmp # # cmp" << endl;
			quat << "label # # start" << endl;
		}
		break;
	case Action_id::_do_while:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //���˺����������Ҫcur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "dowhile";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);

		quat << "dowhile # # " << curSynblLev << endl;
		quat << "label # # start" << endl;
		break;
	case Action_id::_do_while_cmp:
		if (synbl[curSynblLev][0].domainName == "dowhile") {
			quat << "dowhcmp # # #" << endl;
		}
		break;
	case Action_id::_end_dowh:
		if (SEM.top().second == -1) {
			quat << "do " << SEM.top().first << " # #" << endl;
			quat << "jmp # # start" << endl;
			//quat << "end # # dowhile" << endl;
		}
		break;
	case Action_id::_cin:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			quat << "cin # # " << SEM.top().first << endl;
		}
		break;
	case Action_id::_cout:
		if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			tmp = SEM.top();
			if (tokenSeq[SEM.top().second].type = _identifier) {
				//������Ǳ�����ֵ
				if (!isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: ��" << SEM.top().first << "��: δ�����ı�ʶ��" << endl;
					exit(1);
				}
			}
			SEM.pop(); //������ݳ�ջ
			if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum)
			{
				quat << "cout " << SEM.top().first << " # " << tmp.first << endl;
				SEM.pop();
			}
			//else SEM.push(tmp);
			else quat << "cout 10 # " << tmp.first << endl;
		}
		break;
	case Action_id::_init_decl:
	{
		if (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
			int i;
			for (i = 1; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
				//���ñ����Ƿ��Ѿ������
				if (synbl[curSynblLev][i].name == SEM.top().first) {
					//�ظ�����
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2086: ��int " << SEM.top().first << "��: �ض���." << endl;
					exit(1); //�ض���ֱ��ֹͣ����
				}
			}
			tmp = SEM.top();
			tmpNode.prelev = preSynblLev;
			tmpNode.name = tmp.first;
			stack<pair<string, int>> tmpSEM;
			while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
				tmpSEM.push(SEM.top());
				SEM.pop();
			}
			tmpNode.typ = getTypeCode(SEM.top().first).first; //��д���ű��TYP������
			if (tmpNode.typ == -1) {
				//void���ͱ����ڶ��������������
				cout << "Line " << tokenSeq[tmp.second].row << ": ";
				cout << "error C2182: ��" << tmpNode.name << "��: �Ƿ�ʹ�á�void������." << endl;
				exit(1);
			}
			tmpNode.offset = off; //��¼֮ǰ��ƫ����
			off += getTypeCode(SEM.top().first).second; //���µ�ǰƫ����
			//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
			//SEM.pop(); //int��ջ���������ͳ�ջ????????????????????????
			if (!synbl.empty() && curSynblLev < synbl.size()) {
				synbl[curSynblLev].push_back(tmpNode); //�����ű��Ѿ����ڵ����
			//	cout << endl << tmpNode.name << "����synbl[" << curSynblLev << "]" << endl; //for test
			}
			else {
				//��ǰ������״���д���������ű����ڵ����
				tmpSynbl.push_back(tmpNode); //��ǰ�����뵥���ű���
				synbl.push_back(tmpSynbl);
				//	cout << "�����ܱ��½ڵ�" << synbl.size() - 1 << ": " << tmpNode.name << "����";
				//	cout << ", prevel = " << tmpNode.prelev << endl;//for test
			}
			while (!tmpSEM.empty()) { //�ݴ�����ԭ����ջ��
				SEM.push(tmpSEM.top());
				tmpSEM.pop();
			}
		}
	}
	break;
	case Action_id::_init_arr:
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum) {
		//	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
				//vector<SymbolTable> tmpSynbl; //��ʱ�����ű�
				//SymbolTable tmpNode; //��ʱ�����ű���
				tmpNode.name = SEM.top().first;
				pair<string, int> idtmp = SEM.top();
				SEM.pop();//id is out!
				tmpNode.prelev = preSynblLev;
				tmpNode.offset = off;
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					tmpNode.typ = getTypeCode(SEM.top().first).first;
					off += getTypeCode(SEM.top().first).second * (stoi(tmp.first));
					synbl[curSynblLev].push_back(tmpNode);
					//SEM.pop();//int is out
					//SEM.push(idtmp);
				}
			}
		}
		break;
	case Action_id::_struct_scopeinit:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //����һ���µ��򣬽ṹ��������
		tmpNode.prelev = preSynblLev;
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
			tmp = SEM.top();
			tmpNode.domainName = tmp.first;
			SEM.pop(); //id is out!
			if (!SEM.empty() && SEM.top().first == "struct") {
				quat << "struct " << tmp.first << " # " << curSynblLev << endl;
				SEM.pop(); //'struct' is out!
				tmpSynbl.push_back(tmpNode);
				synbl.push_back(tmpSynbl);
			}
			else SEM.push(tmp);
		}
		break;
	}
	
	//for test
	/*stack<pair<string, int>> tmpStack2;
	while (!SEM.empty()) {
		tmpStack2.push(SEM.top());
		SEM.pop();
	}
	while (!tmpStack2.empty()) {
		cout << tmpStack2.top().first << ", ";
		SEM.push(tmpStack2.top());
		tmpStack2.pop();
	}cout << endl;*/
	//showSynbl();
	////for test
	//cout << "****************END********************" << endl;
}

void Syntax::showSynbl() {
	ofstream outSynbl;
	outSynbl.open("synbl.csv");
	for (int i = 0; i < synbl.size(); i++)
	{
		if (i == 0) {
			outSynbl << "Scope " + to_string(i) << ": Global Scope" << endl;
			//cout << "Scope " + to_string(i) << ": Global Scope" << endl;
		}
		else {
			outSynbl << "Scope " + to_string(i) << ": " << synbl[i][0].domainName << endl;
			//cout << "Scope " + to_string(i) << ": " << synbl[i][0].domainName << endl;
		}
		if (synbl[i].size() > 1)outSynbl << "Name,DataType,Offset,Pre-domain" << endl;
		for (int j = 1; j < synbl[i].size(); j++) {
			outSynbl << synbl[i][j].name << ",";
			if (synbl[i][j].typ == 0)outSynbl << "int,";
			else if (synbl[i][j].typ == 1)outSynbl << "float,";
			else if (synbl[i][j].typ == 2)outSynbl << "double,";
			else if (synbl[i][j].typ == 3)outSynbl << "long,";
			else if (synbl[i][j].typ == 4)outSynbl << "short,";
			else if (synbl[i][j].typ == 5)outSynbl << "char,";
			else if (synbl[i][j].typ == -1)outSynbl << "void,";
			outSynbl << synbl[i][j].offset << ",";
			outSynbl << synbl[i][j].prelev << "," << endl;
		}
	}
}
