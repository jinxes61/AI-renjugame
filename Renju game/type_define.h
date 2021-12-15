#ifndef _TYPE_DEFINE_

#define _TYPE_DEFINE_

//Data type declaration

enum pStatus           //棋子状态
{
	BLANK = 0,        //空的
	BLACKp = 1,        //黑棋
	WHITEp = 2         //白棋
};

enum Board             //棋盘信息
{
	START = 20,
	END = 440,
	WID = 30,
	R = 8,
	CENTER = 100       //展示信息的位置
};

enum Button            //四字按钮
{
	BUTTON_WID = 50,              //按钮宽度
	BUTTON_LEN = 150,             //按钮长度
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

enum SMALLB            //两字按钮
{
	SMALLB_WID = 50,
	SMALLB_LEN = 100,
	SURRENDER_X = 480,             //投降按钮起点坐标
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


//棋子信息
typedef struct Point
{
	int row;         //行
	int col;         //列(数字）
	int status;      //棋子状态
}Point;

//评估函数返回值
typedef struct Value
{
	int row;
	int col;
	int val;
}value;

//链表节点
typedef struct Node
{
	char name[20];
	int score;          //步数
	Node* next;
}node;


#endif // !_TYPE_DEFINE_