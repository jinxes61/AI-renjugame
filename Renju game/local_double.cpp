#include "local_double.h"
#include "board.h"

#define SIZE 15

extern int chess[SIZE][SIZE];
extern Point playback[SIZE * SIZE];
extern int musicOn;

void getMou(int* x, int* y)
{
	MOUSEMSG mou;
	mou = GetMouseMsg();
	while (mou.uMsg != WM_LBUTTONDOWN)
	{
		mou = GetMouseMsg();
	}
	*x = mou.x;
	*y = mou.y;
}

void localDouble()
{
	int x, y;         //���������������
	int num = 0;      //������Ŀ
	Point now;        //��ǰ����״̬

	memset(chess, BLANK, sizeof(chess));       //��ʼ������
	
	while (1)
	{
		getMou(&x, &y);         //��ȡ���λ��

		//����
		if (x >= START - WID / 2 && x <= END + WID / 2 && y >= START - WID / 2 && y <= END + WID /2)
		{
			num++;
			now.status = (num % 2 == 1) ? BLACKp : WHITEp;
			if (putdown(&now, x, y))
			{
				playback[num - 1] = now;           //����ÿһ��

				if (judge(now))
				{
					showResult(now.status, num);
					Start();
				}
			}
			else
				num--;
		}

		else if (x >= EXIT_X && x <= EXIT_X + SMALLB_LEN && y >= EXIT_Y && y <= EXIT_Y + SMALLB_WID)
		{
			HWND hwnd = GetDesktopWindow();
			int result = MessageBoxA(hwnd, "ʤ��δ�֣��Ƿ��˳���", "�˳�����", MB_YESNO |MB_SYSTEMMODAL);
			if (result == IDYES)
				Start();
		}

		//ƽ��
		if (num == 225)
		{
			showResult(0, num);
			break;
		}
	}
}

int putdown(Point * now, int moux, int mouy)       //������
{
	int x, y, dis;
	x = (moux - START) / WID;
	y = (mouy - START) / WID;
	dis = moux - START - x * WID;               //���㵽���ϱ��ߵľ���
	if (dis < (WID / 2))
		now->row = x;
	else
		now->row = x + 1;
	dis = mouy - START - y * WID;               //���㵽������ߵľ���
	if (dis < (WID / 2))
		now->col = y;
	else
		now->col = y + 1;
	if (chess[now->row][now->col] != BLANK)
	{
		HWND hwnd = GetDesktopWindow();
		int result = MessageBoxA(hwnd, "�˴�������", "�ظ�����", MB_OK | MB_SYSTEMMODAL);
		return 0;
	}
	chess[now->row][now->col] = now->status;
	showPiece(*now);
	return 1;
}

void showPiece(const Point now)           //��ʾ���µ�����
{
	int x = START + now.row * WID;
	int y = START + now.col * WID;
	if (now.status == BLACKp)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 0.01);
	fillcircle(x, y, R);
}

void setstyle()
{
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 48;						// ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	settextstyle(&f);						// ����������ʽ
}

void showResult(int winner, int num)      //0:ƽ��
{
	char name[10];
	HWND hwnd = GetDesktopWindow();
	if (winner == BLACKp)
	{
		HWND hwnd = GetDesktopWindow();
		int result = MessageBoxA(hwnd, "����ʤ��", "���", MB_YESNO | MB_SYSTEMMODAL);
	}
	else if (winner == WHITEp)
	{
		HWND hwnd = GetDesktopWindow();
		int result = MessageBoxA(hwnd, "����ʤ��", "���", MB_YESNO | MB_SYSTEMMODAL);
	}
	else
	{
		HWND hwnd = GetDesktopWindow();
		int result = MessageBoxA(hwnd, "���ֲ���", "���", MB_YESNO | MB_SYSTEMMODAL);
	}
}

int judge(const Point now)    //1:��ǰ���ʤ��0:δ;��ǰ״̬������now
{
	if (judgeLine(now))
		return 1;
	if (judgeRow(now))
		return 1;
	if (judgeDia(now))
		return 1;
	if (judgeBdia(now))
		return 1;
	return 0;
}

int judgeLine(const Point now)     //1ʤ��,�ж���
{
	int sum = 0;
	int a = now.row, b = now.col;
	int piece = chess[a][b];     //��ǰλ�õ�״̬
	for (int i = a; i < SIZE; i++)
	{
		if (chess[i][b] == piece)
			sum++;
		else
			break;
	}
	for (int i = a - 1; i >= 0; i--)
	{
		if (chess[i][b] == piece)
			sum++;
		else
			break;
	}
	if (sum >= 5)
		return 1;
	else
		return 0;
}

int judgeRow(const Point now)          //�ж���
{
	int sum = 0;
	int a = now.row, b = now.col;
	int piece = chess[a][b];
	for (int i = b; i < SIZE; i++)
	{
		if (chess[a][i] == piece)
			sum++;
		else
			break;
	}
	for (int i = b - 1; i >= 0; i--)
	{
		if (chess[a][i] == piece)
			sum++;
		else
			break;
	}
	if (sum >= 5)
		return 1;
	else
		return 0;
}

int judgeDia(const Point now)
{
	int sum = 0;
	int a = now.row, b = now.col;
	int piece = chess[a][b];
	for (int i = a, j = b; i < SIZE, j < SIZE; i++, j++)
	{
		if (chess[i][j] == piece)
			sum++;
		else
			break;
	}
	for (int i = a - 1, j = b - 1; i >= 0, j >= 0; i--, j--)
	{
		if (chess[i][j] == piece)
			sum++;
		else
			break;
	}
	if (sum >= 5)
		return 1;
	else
		return 0;
}

int judgeBdia(const Point now)
{
	int sum = 0;
	int a = now.row, b = now.col;
	int piece = chess[a][b];
	for (int i = a, j = b; i >= 0, j < SIZE; i--, j++)
	{
		if (chess[i][j] == piece)
			sum++;
		else
			break;
	}
	for (int i = a + 1, j = b - 1; i < SIZE, j >= 0; i++, j--)
	{
		if (chess[i][j] == piece)
			sum++;
		else
			break;
	}
	if (sum >= 5)
		return 1;
	else
		return 0;
}