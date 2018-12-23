#pragma once
#include "c_head.h"

#define SIZE_OF_TOKEN    500				//Token����Ĵ�С
#define SIZE_OF_KEYTAB   33
#define SIZE_OF_DELTAB   45
#define SIZE_OF_OTHERTAB 50

class Token {		  //Token��
public:
	enum TokenType {  //�����Ӧֵ
		_keyword = 1, //�ؼ���
		_identifier,  //��ʶ��
		_delimiter,   //���
		_constnum,    //��������
		_character,   //�ַ�
		_string,      //�ַ���
		_notes,       //ע��(���������Token��)
		_space        //�հ׷�(���������Token��)
	};
	TokenType type;   //����
	int id;			  //��Ӧ���ű��е��±�
	int row;          //�õ�����Դ�����ļ��е����������ڼ��ʱ���������ֵ�����
	Token() { row = 0; } 		    //�޲ι��췽��
	Token(TokenType type, int id) { //�вι��췽��
		this->type = type, this->id = id;
		this->row = 0;
	}
};

class SymbolTable {   //���ű��ܱ��ࣨ��ʶ����
public:
	/*enum Category {
		_function = 1, //��������
		_constant,	   //��������
		_type,		   //��������
		_variable,     //��������
		_vn,           //�����β�
		_vf,           //��ֵ�β�
		_domain        //��������
	};*/
	string name;       //��ʶ��Դ��
	int typ;           //ָ�����ͱ��±�
	//Category cat;	   //�������
	int offset;        //ƫ����
	int prelev;        //ǰһ�����ű�
	string domainName; //����
	SymbolTable() {
		this->offset = 0; 
		this->prelev = -1;
	}
};

struct TypeTable {	   //���ͱ���
	enum VarType {	   //��������
		_int,          //����
		_float,		   //������
		_double,	   //˫����
		_long,		   //��
		_short,        //��
		_char,		   //�ַ���
		_void,         //������
	};
	VarType Tval;      //���루���ͱ��룩
	int Tpoint;        //������������ָ��գ�-1������ָ�������
};