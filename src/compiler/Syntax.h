#pragma once
#include "lex.h"

#define NUM_OF_PRODUTIONS 500
#define SIZE_OF_TAPEL     30  //���ͱ��С
#define C_RULES "Cgrammer.txt"

enum Action_id {
	_push,
	_pop,
	_laber,
	_goto,
	_assi,
	_geq,
	_geq_unary,
	_relation,
	_if,
	_else,
	_while,
	_do,
	_logic,
	_scope_init,
	_param,
	_call,
	_end,
	_return,
	_for,
	_for_inc,
	_for_sec_pre,
	_for_sec_post,
	_for_third_pre,
	_for_third_post,
	_do_while,
	_do_while_cmp,
	_end_dowh,
	_cin,
	_cout,
	_init_decl,
	_init_arr,
	_get_func_name,
	_struct_scopeinit
};


class Syntax: public Lex { 
public:
	typedef struct production {
		string left; //����ʽ��
		vector<string> right;// [10]; //����ʽ�Ҳ�
	}production;
	production prod[NUM_OF_PRODUTIONS];      //����ʽ���飬���ڴ��Ԥ�����Ĳ���ʽ
	int size_of_prod = 0;                    //����ʽ�����±�
	set<string> terminators, non_terminators;//�ս�����Ϻͷ��ս������	 
	map<string, set<string>> First, Follow;  //first���ϡ�follow���� [for example: First(alpha), map(alpha, {First(alpha})
	map<int, set<string>> Select;            //Select set
	map<string, bool> is_deduced_epsilon;    //���ս���Ƿ�����ƿ�
	map<string, vector<string>> tmpStorage;  //��ʱ�洢���һ���󲿷��ս����first����������Ҳ����ս��first����
	map<string, bool> visited;               //���ʱ�ǣ���������
	map<string, int> Action_map;             //���嶯����־ӳ��
	stack<pair<string, int>> SEM;            //����ջ
	TypeTable Tapel[SIZE_OF_TAPEL];          //���ͱ�
	ofstream quat;							 //��Ԫʽ�ļ���д��
	int TapelIndex;                          //���ͱ�����±�
	Syntax();                                //���캯��
	void preProcess(); 
	void dataRevision();
	void DFS_First();
	void getFirst(string curSymbol);
	set<string> int_first(vector<string> alpha);
	void DFS_Follow();
	void getFollow(string curSymbol);
	void getSelect();
	int list_of_LL1(string A, string a);
	map<pair<string, string>, int> CreateLL1List();
	bool LL1_Analyse();
	pair<int,int> getTypeCode(string type);
	void Call(string Action, int TokenIndex, string curstr);
	bool isExistInSynbl(string id, int index);
	int getOffset(string id, int index);
	void showSynbl();
};
