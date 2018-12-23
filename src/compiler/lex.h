#pragma once
#include "SymbolTabClass.h"

class Lex: public Token { //�﷨�������������ַ��ű�
public:
	struct re_table {
		re_table(){}
		vector<pair<regex, TokenType>> table{
			make_pair(regex(R"QWERTY(//.*\n|/\*(.|[\r\n])*?\*/)QWERTY"), _notes), //ƥ��ע��
			make_pair(regex("typedef|void|const|char|int|unsigned|signed|short|long|float|double|sizeof|struct|enum|union|if|else|do|for|while|return|switch|case|default|break|continue|static|include|define|pragma|goto|cin|cout"), _keyword),
			make_pair(regex("[a-zA-Z_][0-9a-zA-Z_]*"), _identifier),
			make_pair(regex("-?[0-9]+((\\.[0-9]+)([eE]-?[0-9]+)|(\\.[0-9]+)|([eE]-?[0-9]+))?[fF]?"), _constnum), //ƥ�両����
			make_pair(regex("-?(0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2}"), _constnum), //ƥ������������ʮ���ơ�ʮ�����ơ��˽��ƣ�
			make_pair(regex("\\+\\+|--|\\+=|-=|\\*=|/=|%=|<<=|>>=|\\|=|\\&=|\\^=|\\+|-|\\*|/|==|>>|<<|=|>=|>|<=|<|;|\\{|\\}|\\(|\\)|\\[|\\]|,|!|%|\\|\\||\\&\\&|\\||\\&|:|#|\\.|->|\\?|~|\\^"), _delimiter),
			make_pair(regex("['][\\s\\S^']?'"), _character),
			make_pair(regex("\".*\""), _string),
			make_pair(regex("\\s+"), _space) //ƥ��հ׷�
		};
	};
	Token tokenSeq[SIZE_OF_TOKEN]; //����token����
	int index_of_token = 0;
	string keyword_table[SIZE_OF_KEYTAB] = { "typedef","void","const","char","int","unsigned","signed","short",
		"long","float","double","sizeof","struct","enum","union","if","else","do","for","while","return",
		"switch","case","default","break","continue","static","include","define","pragma","goto","cin","cout" }; //�ؼ��ֱ�
	string delimiter_table[SIZE_OF_DELTAB] = { "++","--","+=","-=","*=", "/=","%=", "<<=", ">>=","|=","&=", 
		"^=","+","-","*","/","==",">>","<<","=",">=",">","<=","<",";","{","}","(",")","[","]",",","!","%",
		"||","&&","|","&",":","#",".","->","?","~","^" }; //�����
	SymbolTable identifier_table[SIZE_OF_OTHERTAB]; 
	int index_of_idtfer = 0;//��ʶ����
	string constant_table[SIZE_OF_OTHERTAB];	    
	int index_of_const = 0;//������
	string character_table[SIZE_OF_OTHERTAB];		
	int index_of_char = 0;//�ַ���
	string string_table[SIZE_OF_OTHERTAB];			
	int index_of_string = 0;//�ַ�����
	void generateToken(string const &str, int &position);
	void lexicalAnalysis(string Filestream);  //�ʷ�ɨ��������ڣ�����generateToken()������������Ԫʽ
	pair<string, Token::TokenType> NEXT(int pos_of_token);
	void showDelimiterTab(); //��������
	void showKeywordTab();   //����ؼ��ֱ�
};