#ifndef _TYPE_DEFINE_

#define _TYPE_DEFINE_

//Data type declaration

enum pStatus           //����״̬
{
	BLANK = 0,        //�յ�
	BLACKp = 1,        //����
	WHITEp = 2         //����
};

enum Board             //������Ϣ
{
	START = 20,
	END = 440,
	WID = 30,
	R = 8,
	CENTER = 100       //չʾ��Ϣ��λ��
};

enum Button            //���ְ�ť
{
	BUTTON_WID = 50,              //��ť���
	BUTTON_LEN = 150,             //��ť����
	LOCALDOUBLE_X = 470,
	LOCALDOUBLE_Y = 100,
	MVM_X = 470,
	MVM_Y = 320,
	PLAYBACK_X = 470,
	PLAYBACK_Y = 170,
	RULES_X = 470,
	RULES_Y = 240,
	ABOUTUS_X = 470,
	ABOUTUS_Y = 310,
	RANK_X = 470,
	RANK_Y = 380
	
};

enum SMALLB            //���ְ�ť
{
	SMALLB_WID = 50,
	SMALLB_LEN = 100,
	SURRENDER_X = 480,             //Ͷ����ť�������
    SURRENDER_Y = 30,
	EXIT_X = 480,
	EXIT_Y = 125,
	//SUSPEND_X = 480,
	//SUSPEND_Y = 50,
	ONCEMORE_X = 480,
	ONCEMORE_Y = 50,
	BEGIN_X = 600,
	BEGIN_Y = 440
};


//������Ϣ
typedef struct Point
{
	int row;         //��
	int col;         //��(���֣�
	int status;      //����״̬
}Point;

//������������ֵ
typedef struct Value
{
	int row;
	int col;
	int val;
}value;

//����ڵ�
typedef struct Node
{
	char name[20];
	int score;          //����
	Node* next;
}node;


#endif // !_TYPE_DEFINE_