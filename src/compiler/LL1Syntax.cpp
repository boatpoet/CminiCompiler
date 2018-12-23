#include "Syntax.h"

/*---------------------------------------------------------------------------------------------------------------
											Ԥ������(ɨ��һ���ķ������ļ���
����: 1. ����ս�����ϡ����ս������; 2. ���ս����first����; 3. �ж�ÿ�����ս���Ƿ�����ƿ�,���; 4. �ָ����ʽ�����Ҳ�.
----------------------------------------------------------------------------------------------------------------*/
void Syntax::preProcess() {
	ifstream in(C_RULES, ios::in); //��ȡC�ķ��ļ�
	if (!in.is_open()) { //�ķ��ļ��򿪳��������Ǹ��ļ����û�����ɾ������
		cout << "�ķ������ļ���ȡʧ�ܣ��Ҳ������ļ���" << endl;
		return;
	}
	string line_in_rules;
	int index_of_prod = 0;
	while (getline(in, line_in_rules)) {
		if (regex_match(line_in_rules, regex(R"QWERTY(//.*)QWERTY"))) continue; //���˵�ע����
		int ptr_of_rules = 0; //һ���ķ�������ÿ���ַ��ķ���ָ��
		while (line_in_rules[ptr_of_rules] == ' ' || line_in_rules[ptr_of_rules] == '\t') ptr_of_rules++;//�˵��հ׷�
		if (line_in_rules[ptr_of_rules] == ';') continue; //ÿһ���ķ�����Ľ���
		if (isalpha(line_in_rules[ptr_of_rules])) { //��ȡ����ʽ�󲿵ķ��ս��
			string nonTerm = ""; //��ʱ�洢���ս��
			while (line_in_rules[ptr_of_rules] != ' '&&line_in_rules[ptr_of_rules] != '\t')
			{	//�ָ��һ�����ս��
				nonTerm += line_in_rules[ptr_of_rules];
				ptr_of_rules++;
			}
			non_terminators.insert(nonTerm); //���÷��ս�����뵽���ս������
			prod[index_of_prod].left = nonTerm; //��¼�ò���ʽ����
			size_of_prod++; //����ʽ����+1
			while (line_in_rules[ptr_of_rules] == ' ' || line_in_rules[ptr_of_rules] == '\t' || line_in_rules[ptr_of_rules] == ':')
				ptr_of_rules++; //�˵�ð�źͿհ׷�
			while (ptr_of_rules < line_in_rules.size()) { //��¼����ʽ�Ҳ����ţ�˳����д�ս������
														  //һֱ�ߵ����н���
				string tmp = ""; //ƴ���Ҳ�һ������
				if (line_in_rules[ptr_of_rules] == '\'') {
					//��ǰ�������ս������Ҫ��¼���ս��
					ptr_of_rules++; //��ȥ������
					while (line_in_rules[ptr_of_rules] != '\'') {
						tmp += line_in_rules[ptr_of_rules];
						ptr_of_rules++;
					}//ƴ��һ���ս��
					terminators.insert(tmp); //�����ս����¼���ս������
					set<string> tmpset; //��ʱ���ϣ����ڴ洢�ս����First��
					tmpset.insert(tmp); //�ݴ��ս��
					First.insert(make_pair(tmp, tmpset)); //�ս����First�������䱾��
					prod[index_of_prod].right.push_back(tmp); //����ʽ�Ҳ���¼�÷���
					ptr_of_rules += 2; //��ȥ�ս������ĵ����źͿո�
				}
				else { //��ǰ������һ�����ս������һ�����嶯����־
					while (ptr_of_rules < line_in_rules.size() && line_in_rules[ptr_of_rules] != ' ') {
						tmp += line_in_rules[ptr_of_rules];
						ptr_of_rules++;
					}//ƴ��һ�����ս��
					ptr_of_rules++; //��ȥ�ķ�����֮��Ŀո�
					prod[index_of_prod].right.push_back(tmp); //�����ķ����Ż����嶯�����Ŵ浽����ʽ�Ҳ�vector��
					if (tmp == "epsilon") {
						//�ò���ʽ�󲿵ķ��ս������ֱ���ƿ�
						is_deduced_epsilon[prod[index_of_prod].left] = true;
					}
				}
			}
			index_of_prod++;
		}
		else if (line_in_rules[ptr_of_rules] == '|') {
			//һ�����ս���Ƴ�����������ʽ
			ptr_of_rules += 2; //��ȥ'|'�Ϳո�
			prod[index_of_prod].left = prod[index_of_prod - 1].left; //�ò���ʽ�󲿱ض�����һ������ʽ��һ����	
			size_of_prod++;
			while (ptr_of_rules < line_in_rules.size()) { //��¼����ʽ�Ҳ����ţ�˳����д�ս������
														  //һֱ�ߵ����н���
				string tmp = ""; //ƴ���Ҳ�һ������
				if (line_in_rules[ptr_of_rules] == '\'') {
					//��ǰ�������ս������Ҫ��¼���ս��
					ptr_of_rules++; //��ȥ������
					while (line_in_rules[ptr_of_rules] != '\'') {
						tmp += line_in_rules[ptr_of_rules];
						ptr_of_rules++;
					}//ƴ��һ���ս��
					terminators.insert(tmp); //�����ս����¼���ս������
					set<string> tmpset;
					tmpset.insert(tmp);
					First.insert(make_pair(tmp, tmpset));
					prod[index_of_prod].right.push_back(tmp); //����ʽ�Ҳ���¼�÷���
					ptr_of_rules += 2; //��ȥ�ս������ĵ����źͿո�
				}
				else { //��ǰ������һ�����ս�������嶯����־
					while (ptr_of_rules < line_in_rules.size() && line_in_rules[ptr_of_rules] != ' ') {
						tmp += line_in_rules[ptr_of_rules];
						ptr_of_rules++;
					}//ƴ��һ�����ս��
					ptr_of_rules++; //��ȥ�ķ�����֮��Ŀո�
					prod[index_of_prod].right.push_back(tmp); //�����ķ����Ŵ浽����ʽ�Ҳ�vector��
					if (tmp == "epsilon") {
						//�ò���ʽ�󲿵ķ��ս������ֱ���ƿ�
						is_deduced_epsilon[prod[index_of_prod].left] = true;
					}
				}
			}
			index_of_prod++;
		}
	}
	terminators.insert("int_const"); //������Ӽ����ս��
	First["int_const"].insert("int_const");
	terminators.insert("char_const");
	First["char_const"].insert("char_const");
	terminators.insert("id");
	First["id"].insert("id");
	terminators.insert("float_const");
	First["float_const"].insert("float_const");
	terminators.insert("string");
	First["string"].insert("string");

	//for Test Output
	/*int cnt = 0;
	cout << "�ս������Ϊ��" << endl;
	for (set<string>::iterator it = terminators.begin(); it != terminators.end(); it++, cnt++)
	{
		cout << *it << "   ";
		if (cnt == 2) {
			cout << endl;
			cnt = 0;
		}
	}
	cnt = 0;
	cout << "\n\n���ս������Ϊ��" << endl;
	for (set<string>::iterator it = non_terminators.begin(); it != non_terminators.end(); it++, cnt++)
	{
		cout << *it << "   ";
		if (cnt == 2) {
			cout << endl;
			cnt = 0;
		}
	}*/
	
	/*cout << "\n\n����First���ϣ�" << endl;
	for (map<string, set<string>>::iterator it = First.begin(); it != First.end(); it++) {
	cout << "First(" << it->first << ") = ";
	for (set<string>::iterator _it = it->second.begin(); _it != it->second.end(); _it++)
	cout << *_it << "  ";
	cout << endl;
	}
	cout << "\n\n�������ƿռ��ϣ�" << endl;
	for (map<string, bool>::iterator it = is_deduced_epsilon.begin(); it != is_deduced_epsilon.end(); it++) {
	cout << it->first << endl;
	}*/
	//for Test Output
	in.close(); //�ر��ļ�
}

//�ж�һ���ַ����Ƿ�ȫΪ��д��ĸ,�Դ������ķ����ź����嶯������
bool isUpper(string str) {
	if (regex_match(str, regex("[A-Z_0-9]+")))return true;
	else return false;
}
/*---------------------------------------------------------------------------------------------------------------
						�ڶ���ɨ�辭��Ԥ����Ĳ���ʽ���飬���������пձ����ɿ��������first����.
----------------------------------------------------------------------------------------------------------------*/
void Syntax::dataRevision() { //��������--�ڶ���Ԥ���������һ��û�н��������
	//�ȵ���ɨһ��
	for (int i = size_of_prod - 1; i >= 0; i--) {
		if (!is_deduced_epsilon[prod[i].left]) { //ԭ���ƿձ�־Ϊfalse
			int index_of_right = 0;
			//bool isAction = false; //�Ƿ�Ϊ���嶯����־
			while (index_of_right < prod[i].right.size() &&
				(non_terminators.find(prod[i].right[index_of_right]) != non_terminators.end()
					|| isUpper(prod[i].right[index_of_right]))) {
				//�������ʽ�Ҷ�Ϊ���ս�������嶯����־
				if (isUpper(prod[i].right[index_of_right])) index_of_right++; //���嶯����־ֱ������
				else { //�Ƿ��ս��
					if (!is_deduced_epsilon[prod[i].right[index_of_right]]) {
						is_deduced_epsilon[prod[i].left] = false;
						break;
					}
					else index_of_right++;
				}
			}
			if (index_of_right >= prod[i].right.size()) { //����ʽ�Ҷ����з��Ŷ������ƿ�
				is_deduced_epsilon[prod[i].left] = true;
				First[prod[i].left].insert("epsilon");
			}
		}
	}
	//������ɨһ��
	for (int i = 0; i < size_of_prod; i++) {
		if (!is_deduced_epsilon[prod[i].left]) { //ԭ���ƿձ�־Ϊfalse
			int index_of_right = 0;
			while (index_of_right < prod[i].right.size() &&
				(non_terminators.find(prod[i].right[index_of_right]) != non_terminators.end()
					|| isUpper(prod[i].right[index_of_right]))) {
				//�������ʽ�Ҷ�Ϊ���ս�������嶯����־
				if (isUpper(prod[i].right[index_of_right])) index_of_right++; //���嶯����־ֱ������
				else { //�Ƿ��ս��
					if (!is_deduced_epsilon[prod[i].right[index_of_right]]) {
						is_deduced_epsilon[prod[i].left] = false;
						break;
					}
					else index_of_right++;
				}
			}
			if (index_of_right >= prod[i].right.size()) { //����ʽ�Ҷ����з��Ŷ������ƿ�
				is_deduced_epsilon[prod[i].left] = true;
				First[prod[i].left].insert("epsilon");
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------------------------
					���һ���������������ɨ�����ʽ����first���������, ����������DFS_First()
										��First(T), T -> Vn or Vt
----------------------------------------------------------------------------------------------------------------*/
void Syntax::DFS_First() {
	for (set<string>::iterator it = non_terminators.begin(); it != non_terminators.end(); it++)
		visited.insert(make_pair(*it, false)); //��ʼ��
	for (set<string>::iterator it = non_terminators.begin(); it != non_terminators.end(); it++)
	{
		if (!visited[*it]) //����÷���δ������
			getFirst(*it);//����֮
	}	
}
void Syntax::getFirst(string curSymbol) {
	
	visited[curSymbol] = true; //���÷��ŵķ��ʱ�־��Ϊtrue�������ѱ�����
	for (int index_prod = 0; index_prod < size_of_prod; index_prod++)
	{	//��������ʽ��
		
		if (prod[index_prod].left == curSymbol) { //�ҵ��÷��Ŷ�Ӧ�Ĳ���ʽ
			int index_right = 0; //��ǰ����ʽ�Ҳ����ż�������
			if (isUpper(prod[index_prod].right[index_right])) index_right++; //����Ҳ��׷�����һ�������־��������
			if (non_terminators.find(prod[index_prod].right[index_right]) != non_terminators.end()) {
				//����ʽ�Ҳ��׷���Ϊ���ս��
				vector<string> tmpvec;
				tmpvec.push_back(prod[index_prod].right[index_right]); //��ʽת�� string -> vector<string>
				tmpStorage.insert(make_pair(prod[index_prod].left, tmpvec)); //�ݴ�֮
				if (!visited[prod[index_prod].right[index_right]]) //����÷���δ�����ʹ�!!!!!!!!
					getFirst(prod[index_prod].right[index_right]); //��ȡ�÷��ŵ�first����
				set<string> t_set;
				t_set = First[prod[index_prod].right[index_right]];
				if (is_deduced_epsilon[prod[index_prod].right[index_right]]) {
					//����÷��ſ����ƿ�  First type is: map<string, set<string>>
					t_set.erase("epsilon");
				}
				First[prod[index_prod].left].insert(t_set.begin(), t_set.end()); //�ϲ����󲿷��ŵ�first����
				while (is_deduced_epsilon[prod[index_prod].right[index_right]]) {
					//����ò���ʽ�Ҳ��׷��ſ����ƿ� 
					next_symb: index_right++; //�����һ��������һ������
					if (index_right < prod[index_prod].right.size())
					{	//����Ҳ��÷��ź��滹�з���
						if (isUpper(prod[index_prod].right[index_right])) {
							//�������嶯����־,����
							goto next_symb;
						}
						if (non_terminators.find(prod[index_prod].right[index_right]) != non_terminators.end()) {
							//��������������Ҳ�Ƿ��ս��
							tmpvec.push_back(prod[index_prod].right[index_right]);
							tmpStorage[prod[index_prod].left] =  tmpvec; //�ݴ�֮
							if (!visited[prod[index_prod].right[index_right]]) //����÷���δ�����ʹ�!!!!!!
								getFirst(prod[index_prod].right[index_right]); //����֮
							//else { //����÷����ѱ����ʹ�
								set<string> _set;
								_set = First[prod[index_prod].right[index_right]];
								if (is_deduced_epsilon[prod[index_prod].right[index_right]]) {
									//����÷��ſ����ƿ�  First type is: map<string, set<string>>
									_set.erase("epsilon");
								}
								First[prod[index_prod].left].insert(_set.begin(), _set.end()); //�ϲ����󲿷��ŵ�first����
						}
						else First[prod[index_prod].left].insert(prod[index_prod].right[index_right]);
						//��������������ս���������󲿷���first������
					}
					else break;
				}
			}
			//����ʽ�Ҳ��׷���Ϊ�ս����epsilon, ��֮�����󲿷��ŵ�first����
			else {
				First[prod[index_prod].left].insert(prod[index_prod].right[index_right]);
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------------------------
						��First(alpha),alpha -> (Vn + Vt)*��������Select����First��ں�����
----------------------------------------------------------------------------------------------------------------*/
set<string> Syntax::int_first(vector<string> alpha)//first�ӿ�--��ں���
{
	int index_right = 0;
	if (regex_match(alpha[index_right], regex("[A-Z_0-9]+")))index_right++; //�׷�Ϊ���嶯����־������
	if (alpha[index_right] == "epsilon" || terminators.find(alpha[index_right]) != terminators.end()
		|| (non_terminators.find(alpha[index_right]) != non_terminators.end() && !is_deduced_epsilon[alpha[index_right]]))
	{
		//�������ʽ�Ҳ��׷����Ǧ� �� �ս�� �� �������ƿյķ��ս��
		set<string> tmpset;
		if (alpha[index_right] == "epsilon") { //���ĳ������ʽ�Ҳ�����һ����
			tmpset.insert("epsilon");
			return tmpset;
		}
		return First[alpha[index_right]];
	}
	else {//����ʽ�Ҳ��׷����ǿ����ƿյķ��ս��
		set<string> tmpset;
		while (index_right < alpha.size() &&
			((non_terminators.find(alpha[index_right]) != non_terminators.end() &&
			is_deduced_epsilon[alpha[index_right]]) || isUpper(alpha[index_right]))) {
			//�������ʽ�Ҳ��ǿ����ƿյķ��ս��
			if (regex_match(alpha[index_right], regex("[A-Z_0-9]+"))) {
				//�������嶯�����ţ�������ֱ��ƥ�������һ���̶������Ч�ʣ����ٳ�����ת��
				index_right++;
				continue;
			}
			tmpset.insert(First[alpha[index_right]].begin(), First[alpha[index_right]].end());
			tmpset.erase("epsilon");
			index_right++;
		}
		if (index_right >= alpha.size()) {
			//�Ҳ�ȫ�����ƿ�
			tmpset.insert("epsilon");
		}
		else { //�������޷��ƿյķ���
			tmpset.insert(First[alpha[index_right]].begin(), First[alpha[index_right]].end());
		}
		return tmpset;
	}
}
/*---------------------------------------------------------------------------------------------------------------
												��Follow����
----------------------------------------------------------------------------------------------------------------*/
void Syntax::DFS_Follow()
{
	for (set<string>::iterator it = non_terminators.begin(); it != non_terminators.end(); it++) 
		visited[*it] = false; //�ٴγ�ʼ�����ʱ�־����
	for (set<string>::iterator it = non_terminators.begin(); it != non_terminators.end(); it++)
		if (!visited[*it])
			getFollow(*it);
}
void Syntax::getFollow(string curSymbol) {//First type is: map<string, set<string>>
	visited[curSymbol] = true;
	if (curSymbol == prod[0].left)//�����ǰ����Ϊ��ʼ���ţ��Ҹ÷��ŵ�follow����δ����
		Follow[curSymbol].insert("#");
	for (int i = 0; i < size_of_prod; i++) {
		//��������ʽ��
		int index_right = 0;
		vector<string>::iterator it = find(prod[i].right.begin(), prod[i].right.end(), curSymbol);
		while (it != prod[i].right.end()) 
		{ //����ò���ʽ�Ҳ������ҵ��������
			index_right = it - prod[i].right.begin(); //������ת��Ϊ����ֵ
			index_right++;
			if (index_right < prod[i].right.size() && regex_match(prod[i].right[index_right], regex("[A-Z_0-9]+"))) index_right++; //�÷��ź�����һ�������־������
			while (index_right < prod[i].right.size() && (is_deduced_epsilon[prod[i].right[index_right]]
				|| isUpper(prod[i].right[index_right]))) {
				//�������ʽ�Ҳ��÷��ս�����滹�з��� �Һ���ķ��ſ����ƿջ��ߺ�����һ�������־
				if (regex_match(prod[i].right[index_right], regex("[A-Z_0-9]+"))) {
					index_right++;
					continue;
				} //�������嶯����־��������
				set<string> tmp;
				tmp = First[prod[i].right[index_right]];
				tmp.erase("epsilon");
				Follow[prod[i].right[it - prod[i].right.begin()]].insert(tmp.begin(), tmp.end());
				index_right++;
			}
			if (index_right < prod[i].right.size() && !is_deduced_epsilon[prod[i].right[index_right]]) //�����������һ�������Ʋ�����, ������First��Ҳ�ӽ���
			{
				Follow[prod[i].right[it - prod[i].right.begin()]].insert(First[prod[i].right[index_right]].begin(), First[prod[i].right[index_right]].end());
				it = find(prod[i].right.begin() + index_right, prod[i].right.end(), curSymbol);
			}
			if (index_right >= prod[i].right.size()) //�������ķ���ȫ�������ƿ�
			{
				if (!visited[prod[i].left]) getFollow(prod[i].left); //û�з��ʹ�������֮
				Follow[prod[i].right[it - prod[i].right.begin()]].insert(Follow[prod[i].left].begin(), Follow[prod[i].left].end()); //���ʹ����Ѹò���ʽ�󲿷��ŵ�Follow���ӽ���
				it = prod[i].right.end();
			}
			
		}
	}
}
/*---------------------------------------------------------------------------------------------------------------
												��Select����
----------------------------------------------------------------------------------------------------------------*/
void Syntax::getSelect() {
	//��select����
	for (int i = 0; i < size_of_prod; i++) {
		//��������ʽ����
		//bool is_all_epsilon = false;
		int index_right = 0;
		while (index_right < prod[i].right.size()
			&& ((non_terminators.find(prod[i].right[index_right]) != non_terminators.end()
			&& is_deduced_epsilon[prod[i].right[index_right]]) 
			|| prod[i].right[0] == "epsilon" || isUpper(prod[i].right[index_right]))) {
			//����ò���ʽ�Ҳ��׷���Ϊ���ս�� �� �����ƿ�
			index_right++;
		}
		if (index_right >= prod[i].right.size()) //�������ʽ�Ҳ�����ȫ�������ƿ�, alpha =>* epsilon
		{
			set<string> tmpset, first, follow;
			first = int_first(prod[i].right);
			first.erase("epsilon");
			follow = Follow[prod[i].left];
			set_union(first.begin(), first.end(), follow.begin(), follow.end(), inserter(tmpset, tmpset.begin()));
			Select[i] = tmpset;
		}
		else { //alpha ��>* epsilon
			Select[i] = int_first(prod[i].right);
		}
	}
}
/*---------------------------------------------------------------------------------------------------------------
												��LL1��������
----------------------------------------------------------------------------------------------------------------*/
int Syntax::list_of_LL1(string A, string a) //L(A, a) = i ('i' is index of production)
{
	for (int i = 0; i < size_of_prod; i++) {
		if (prod[i].left == A && Select[i].find(a)!=Select[i].end()) {
			return i;
		}
	}
	return -1;
}



