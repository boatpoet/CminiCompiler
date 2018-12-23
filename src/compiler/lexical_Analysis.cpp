/*-------�ʷ�����ɨ����-------*/
#include"lex.h"

ofstream outLex;

void Lex::lexicalAnalysis(string Filestream) {
	int pos = 0;
	outLex.open("Token.csv");
	outLex << "Symbol,TokenType,List-ID,Line-Number" << endl;
	while (pos < Filestream.size()) {
		generateToken(Filestream, pos);
	}
	outLex.close();
}

void Lex::generateToken(string const &str, int &position)
{
	static const re_table reg;
	if (position > str.size() || position < 0) return;
	auto it = str.begin() + position; //��ǰ��ƥ�䴮����ʼλ��
	bool ismatched;//������
	static int row = 1;   //��¼����
	for (auto &e : reg.table) //e -- regex RE
	{
		smatch sm; //match_result
		ismatched = false;//������
		if (regex_search(it, str.end(), sm, e.first, regex_constants::match_continuous)) {
			ismatched = true; //������
			string str_match = sm[0].str();
			if (e.second == _space && (str_match == "\n\t"||str_match == "\n")) {
				row++;
			}
			if (e.second != _space && e.second != _notes)
			{
				tokenSeq[index_of_token].type = e.second;
				tokenSeq[index_of_token].row = row; //��¼��������
				if (e.second == _keyword) {  //�ؼ���
					for (int i = 0; i < SIZE_OF_KEYTAB; i++) 
						if (str_match == keyword_table[i]) {
							tokenSeq[index_of_token].id = i;
							break;
						}
				}
				else if (e.second == _delimiter) { //���
					for (int i = 0; i < SIZE_OF_DELTAB; i++)
						if (str_match == delimiter_table[i]) {
							tokenSeq[index_of_token].id = i;
							break;
						}
				}
				else if (e.second == _identifier) { //��ʶ��
					bool exist = false;
					for (int i = 0; i < index_of_idtfer; i++)
					{
						if (identifier_table[i].name == str_match) //�ñ�ʶ����֮ǰ�Ѿ������
						{
							exist = true;
							tokenSeq[index_of_token].id = i;
							break;
						}
					}
					if (!exist) { //�ñ�ʶ��Ϊ�³��ֱ�ʶ����������ʶ����
						identifier_table[index_of_idtfer].name = str_match; //���ʶ����
						tokenSeq[index_of_token].id = index_of_idtfer++;	//��token�м�¼�ñ�ʶ���ڱ�ʶ�����е�λ��
					}
				}
				else if (e.second == _constnum) {
					constant_table[index_of_const] = str_match;   //�����ATTENTION���������⣬���������ַ������ͣ�Ϊδת�������ͣ���
					tokenSeq[index_of_token].id = index_of_const++;
				}
				else if (e.second == _character) {
					character_table[index_of_char] = str_match.substr(1, str_match.length()-2);   //���ַ���
					tokenSeq[index_of_token].id = index_of_char++;
				}
				else if (e.second == _string) {
					string_table[index_of_string] = str_match.substr(1, str_match.length()-2);   //���ַ�����
					tokenSeq[index_of_token].id = index_of_string++;
				}
				//--------OUTPUT---------
				outLex << str_match << "," << tokenSeq[index_of_token].type << "," << tokenSeq[index_of_token].id << "," << tokenSeq[index_of_token].row << endl;
				//cout << setw(10) << str_match << setw(7) << "{" << tokenSeq[index_of_token].type << "," << tokenSeq[index_of_token].id << "}\t";
				//cout << "row = " << tokenSeq[index_of_token].row << endl;
				//--------OUTPUT---------
				index_of_token++;
			}
			position += str_match.size();
			break;
		}
	}
	if (!ismatched) { //������
		cout << "ERROR" << endl; exit(1);
	}
}

void Lex::showKeywordTab() {   //����ؼ��ֱ�
	ofstream key;
	key.open("keyword.csv");
	for (int i = 0; i < SIZE_OF_KEYTAB; i++) {
		key << keyword_table[i] << endl;
	}
	key.close();
}

void Lex::showDelimiterTab() { //��������
	ofstream del;
	del.open("delimiter.csv");
	for (int i = 0; i < SIZE_OF_DELTAB; i++) {
		del << delimiter_table[i] << endl;
	}
	del.close();
}

pair<string, Token::TokenType> Lex::NEXT(int pos_of_token)
{
	pair<string, Token::TokenType> w;
	if (tokenSeq[pos_of_token].type == _keyword) //�ؼ���
		w = make_pair(keyword_table[tokenSeq[pos_of_token].id], _keyword);
	else if (tokenSeq[pos_of_token].type == _delimiter) //���
		w = make_pair(delimiter_table[tokenSeq[pos_of_token].id], _delimiter);
	else if (tokenSeq[pos_of_token].type == _identifier) //��ʶ��
		w = make_pair(identifier_table[tokenSeq[pos_of_token].id].name, _identifier);
	else if (tokenSeq[pos_of_token].type == _constnum) //����
		w = make_pair(constant_table[tokenSeq[pos_of_token].id], _constnum);
	else if (tokenSeq[pos_of_token].type == _character) //�ַ�
		w = make_pair(character_table[tokenSeq[pos_of_token].id], _character);
	else if (tokenSeq[pos_of_token].type == _string) //�ַ���
		w = make_pair(string_table[tokenSeq[pos_of_token].id], _string);
	return w;
}
