#define _CRT_SECURE_NO_WARNINGS
#include "board.h"

#ifndef CHESS
#define CHESS

extern int chess[SIZE][SIZE] = { 0 };
int musicOn;

#endif // !CHESS

void setbkg()
{
//铺设背景
	IMAGE text;
	loadimage(&text, _T("text.png"));
	putimage(0, 0, &text);     
}

void setbutton()
{
	//贴上按钮
	IMAGE localdouble;              //本地双人
	loadimage(&localdouble, _T("localdouble.png"), BUTTON_LEN, BUTTON_WID);
	putimage(LOCALDOUBLE_X, LOCALDOUBLE_Y, &localdouble);

	IMAGE mvm;          //人机对战
	setbkcolor(WHITE);
	loadimage(&mvm, _T("mvm.png"), BUTTON_LEN, BUTTON_WID);
	putimage(MVM_X, MVM_Y, &mvm);
}


int getchoice()
{
	int x, y, dis;
	MOUSEMSG mou = GetMouseMsg();
	while (mou.uMsg != WM_LBUTTONDOWN)
	{
		mou = GetMouseMsg();
	}
	x = mou.x;
	y = mou.y;
	if (x >= LOCALDOUBLE_X && x <= LOCALDOUBLE_X + BUTTON_LEN)
	{
		if (y >= LOCALDOUBLE_Y && y <= LOCALDOUBLE_Y + BUTTON_WID)
			return 1;
	}
	if (x >= MVM_X && x <= MVM_X + BUTTON_LEN)
	{
		if (y >= MVM_Y && y <= MVM_Y + BUTTON_WID)
			return 2;
	}
}

void Start()
{
	int x, y;
	setbkg();
	setbutton();
	int choice = getchoice();
	if (choice == 1)
	{
		drawBoard();
		setButtonForLocal();
		localDouble();
	}
	else if (choice == 2)
	{
		drawBoard();
		setButtonForLocal();
		manVmachine();
	}
}

void setButtonForLocal()
{
	IMAGE exit;
	loadimage(&exit, _T("exit.png"), SMALLB_LEN, SMALLB_WID);
	putimage(EXIT_X, EXIT_Y, &exit);
}

void setButtonForPlayback()
{
	IMAGE suspend, oncemore, exit;
	loadimage(&exit, _T("exit.png"), SMALLB_LEN, SMALLB_WID);
	//loadimage(&suspend, _T("suspend.png"), SMALLB_LEN, SMALLB_WID);
	loadimage(&oncemore, _T("oncemore.png"), SMALLB_LEN, SMALLB_WID);
	putimage(EXIT_X, EXIT_Y, &exit);
	//putimage(SUSPEND_X, SUSPEND_Y, &suspend);
	putimage(ONCEMORE_X, ONCEMORE_Y, &oncemore);


}

void drawBoard()
{
	IMAGE backgroundimg;
	loadimage(&backgroundimg, _T("bkg.jpg"));
	putimage(0, 0, &backgroundimg);

	setlinecolor(BLACK);
	setlinestyle(0 | PS_JOIN_BEVEL, 1);
	for (int i = START; i <= END; i += WID)
	{
		line(START, i, END, i);
		line(i, START, i, END);
	}
	setlinecolor(BLACK);
}

void showAllpieces()
{
	int x, y;                     //棋子中心坐标
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 0.01);
	for(int i = 0; i < SIZE; i ++)
		for (int j = 0; j < SIZE; j++)
		{
			x = i * WID + START;                //图形与数组的x,y相反
			y = j * WID + START;
			if (chess[i][j] == BLACKp)
			{
				setfillcolor(BLACK);
				fillcircle(x, y, R);
			}
			else if (chess[i][j] == WHITEp)
			{
				setfillcolor(WHITE);
				fillcircle(x, y, R);
			}
		}
}
