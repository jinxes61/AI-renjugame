#include "man_machine.h"
#include<time.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
int start;

void manVmachine()
{ 
	value res;
	int x, y, val, color;         //储存鼠标点击的坐标
	
	int num = 0;      //棋子数目
	Point now;        //当前落子状态

	memset(chess, BLANK, sizeof(chess));       //初始化棋盘
	
	while (1)
	{
		if (num % 2 == 1)
		{
  			now.status = WHITEp;
			start = clock();
			int dep = 4;
			
			res = getMaxValue(dep, WHITEp, -inf, inf, dep);
			++dep;
			//if (clock() - 3000 > start) break;

			now.row = res.row;
			now.col = res.col;
			showPiece(now);
			chess[now.row][now.col] = WHITEp;
			num++;
			if (judge(now))
			{
				showResult(now.status, num);
				Start();
			}
			continue;
		}
		getMou(&x, &y);
		if (x >= START - WID / 2 && x <= END + WID / 2 && y >= START - WID / 2 && y <= END + WID / 2)    //在棋盘内
		{
			num++;
			now.status = (num % 2 == 1) ? BLACKp : WHITEp;
			if (putdown(&now, x, y))
			{

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
			Start();
		}
	}
}

inline int tooFar(int x, int y)
{
	if (x > 0 && chess[x - 1][y] != BLANK)
		return 0;
	if (x > 1 && chess[x - 2][y] != BLANK)
		return 0;
	if (x != SIZE && chess[x + 1][y] != BLANK)
		return 0;
	if (x != SIZE - 1 && chess[x + 2][y] != BLANK)
		return 0;
	if (y > 0 && chess[x][y - 1] != BLANK)
		return 0;
	if (y > 1 && chess[x][y - 2] != BLANK)
		return 0;
	if (y != SIZE && chess[x][y + 1] != BLANK)
		return 0;
	if (y != SIZE - 1 && chess[x][y + 2] != BLANK)
		return 0;
	//左上角
	if (x > 0 && y > 0 && chess[x - 1][y - 1] != BLANK)
		return 0;
	if (x > 1 && y > 1 && chess[x - 2][y - 2] != BLANK)
		return 0;
	//右下角
	if (x != SIZE && y != SIZE && chess[x + 1][y + 1] != BLANK)
		return 0;
	if (x != SIZE - 1 && y != SIZE - 1 && chess[x + 2][y + 2] != BLANK)
		return 0;
	//右上角x+ y-
	if (x != SIZE && y > 0 && chess[x + 1][y - 1] != BLANK)
		return 0;
	if (x != SIZE - 1 && y > 1 && chess[x + 2][y - 2] != BLANK)
		return 0;
	//左下角x- y+
	if (x > 0 && y != SIZE && chess[x - 1][y + 1] != BLANK)
		return 0;
	if (x >1 && y != SIZE - 1 && chess[x - 2][y + 2] != BLANK)
		return 0;
	return 1;
	
}

bool cmp(const value& a, const value& b)
{
	return a.val > b.val;
}

value getMaxValue(int leftstep, int color, int alpha, int beta, int dep)
{
	value temp;
	temp.col = 0; temp.row = 0; temp.val = 0;
	if (leftstep == 0)
	{
		temp.val = evaluate(color);
		return temp;
	}

	value step[200];
	int d = 0;

	for (int i = 0; i < SIZE; i ++)
		for (int j = 0; j < SIZE; j ++)
			if (chess[i][j] == BLANK && !tooFar(i, j))
			{
				int val;
				chess[i][j] = color;
				val = evaluate(color);
				if (val > 800000)
				{
					chess[i][j] = 0;
					if (leftstep == dep)
					{
						temp.row = i;
						temp.col = j;
					}
					temp.val = val;
					return temp;
				}
				step[++d].row = i; step[d].col = j;
				step[d].val = val;
				chess[i][j] = BLANK;
			}
	std::sort(step + 1, step + 1 + d, cmp);
	for (int i = 1; i <= d; i++)
	{
		int val, p = step[i].row, q = step[i].col;
		chess[p][q] = color;
		val = -getMaxValue(leftstep - 1, 3 - color, -beta, -alpha, dep).val;
		chess[p][q] = BLANK;
		if (val >= beta)
		{
			temp.val = beta;
			return temp;
		}
		if (val > alpha)
		{
			alpha = val;
			if (leftstep == dep)
			{
				temp.row = p;
				temp.col = q;
			}
		}
	}
	temp.val = alpha;
	return temp;
}


int evaluate(int color)
{
	//判断行
	Point a, b;
	a.status = color;
	b.status = 3 - color;
	int val = 0;
	val += LigatureOnLine(a) - LigatureOnLine(b);
	val += LigatureOnRow(a) - LigatureOnRow(b);
	val += LigatureOnDia(a) - LigatureOnDia(b);
	val += LigatureOnBdia(a) - LigatureOnDia(b);
	return val;
}

int LigatureOnLine(const Point now)
{
	int num = 0, val = 0;             //同子个数,对方个数，价值,是否被计分过
	for (int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j ++)
			if (chess[i][j] == now.status)
			{
				num = 0;
				for (int k = j; k < j + 5; k++)
				{
					if (chess[i][k] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				if (num == 5)
				{
					val += 1000000;
					j += 4;
					continue;
				}
				if (num == 4)
				{
					//中间缺
					if (chess[i][j + 2] == BLANK)
					{
						val += 2600;
						j += 4;
						continue;
					}
					else if (chess[i][j + 1] == BLANK || chess[i][j + 3] == BLANK)
					{
						val += 3000;
						j += 4;
						continue;
					}
				}

				//四个
				num = 0;
				for (int k = j; k < j + 4; k++)
				{
					if (chess[i][k] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				//四子
				if (num == 4)
				{
					//边界情况
					if (j == 0)
					{
						if (chess[i][j + 4] == BLANK)
						{
							val += 2500;
							j += 3;
							continue;
						}
					}
					else if (j == 11)
					{
						if (chess[i][j - 1] == BLANK)
						{
							val += 2500;
							j += 3;
							break;
						}
					}
					else if (chess[i][j - 1] != BLANK)
					{
						if (chess[i][j + 4] == BLANK)
						{
							val += 2500;
							j += 3;
							continue;
						}
					}
					else if (chess[i][j + 4] == BLANK)
					{
						val += 300000;
						j += 3;
						continue;
					}
					else
					{
						val += 2500;
						j += 3;
						continue;
					}
				}

				//三子
				num = 0;
				for (int k = j; k < j + 3; k++)
				{
					if (chess[i][k] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				if (num == 3)
				{
					//边界
					if (j == 0)
					{
						if (chess[i][j + 3] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else if (j == 12)
					{
						if (chess[i][j - 1] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else if (chess[i][j - 1] != BLANK)
					{
						if (chess[i][j + 3] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else
					{
						//活三
						if (chess[i][j + 3] == BLANK)
						{
							val += 3000;
							j += 2;
							continue;
						}
						else
						{
							val += 500;
							j += 2;
							continue;
						}
					}
				}
				if (j != 0 && j != 13 && chess[i][j] == chess[i][j + 1]
					&& chess[i][j] != BLANK
					&& chess[i][j - 1] == BLANK && chess[i][j + 2] == BLANK)
				{
					val += 50;
					j += 1;
				}
			}
	return val;
}


int LigatureOnRow(const Point now)
{
	int num = 0, val = 0;             //同子个数,对方个数，价值,是否被计分过
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (chess[j][i] == now.status)
			{
				num = 0;
				for (int k = j; k < j + 5; k++)
				{
					if (chess[k][i] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				if (num == 5)
				{
					val += 1000000;
					j += 4;
					continue;
				}
				if (num == 4)
				{
					//中间缺
					if (chess[j + 2][i] == BLANK)
					{
						val += 2600;
						j += 4;
						continue;
					}
					else if (chess[j + 1][i] == BLANK || chess[j + 3][i] == BLANK)
					{
						val += 3000;
						j += 4;
						continue;
					}
				}

				//四个
				num = 0;
				for (int k = j; k < j + 4; k++)
				{
					if (chess[k][i] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				//四子
				if (num == 4)
				{
					//边界情况
					if (j == 0)
					{
						if (chess[j + 4][i] == BLANK)
						{
							val += 2500;
							j += 3;
							continue;
						}
					}
					else if (j == 11)
					{
						if (chess[j - 1][i] == BLANK)
						{
							val += 2500;
							j += 3;
							break;
						}
					}
					else if (chess[j - 1][i] != BLANK)
					{
						if (chess[j + 4][i] == BLANK)
						{
							val += 2500;
							j += 3;
							continue;
						}
					}
					else if (chess[j + 4][i] == BLANK)
					{
						val += 300000;
						j += 3;
						continue;
					}
					else
					{
						val += 2500;
						j += 3;
						continue;
					}
				}

				//三子
				num = 0;
				for (int k = j; k < j + 3; k++)
				{
					if (chess[k][i] == now.status)
						num++;
					if (k == SIZE)
						break;
				}
				if (num == 3)
				{
					//边界
					if (j == 0)
					{
						if (chess[j + 3][i] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else if (j == 12)
					{
						if (chess[j - 1][i] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else if (chess[j - 1][i] != BLANK)
					{
						if (chess[j + 3][i] == BLANK)
						{
							val += 500;
							j += 2;
							continue;
						}
					}
					else
					{
						//活三
						if (chess[j + 3][i] == BLANK)
						{
							val += 3000;
							j += 2;
							continue;
						}
						else
						{
							val += 500;
							j += 2;
							continue;
						}
					}
				}
				if (j != 0 && j != 13 && chess[j][i] == chess[j + 1][i]
					&& chess[j][i] != BLANK
					&& chess[j - 1][i] == BLANK && chess[j + 2][i] == BLANK)
				{
					val += 50;
					j += 1;
				}
			}
	return val;
}


int LigatureOnDia(const Point now)
{
	int num = 0, val = 0;
	for (int n = 0; n < SIZE; n ++)
		for(int i = n, j = 0; i < SIZE; i ++, j ++)
			if (chess[i][j] == now.status)
			{
				num = 0;
				for (int x = i, y = j; x < i + 5; x ++, y ++)
				{
					if (chess[x][y] == now.status)
						num++;
					if (x == SIZE || y == SIZE)
						break;
				}
				if (num == 5)
				{
					val += 1000000;
					i += 4;
					j += 4;
					continue;
				}
				if (num == 4)
				{
					//中间缺
					if (chess[i + 2][j + 2] == BLANK)
					{
						val += 2600;
						i += 4;
						j += 4;
						continue;
					}
					else if (chess[i + 1][j + 1] == BLANK || chess[i + 3][j + 3] == BLANK)
					{
						val += 3000;
						i += 4;
						j += 4;
						continue;
					}
				}

				//四个
				num = 0;
				for (int x = i, y = j; x < i + 4 && y < j + 4; x++, y++)
				{
					if (chess[x][y] == now.status)
						num++;
					if (x == SIZE || y == SIZE)
						break;
				}
				//四子
				if (num == 4)
				{
					//边界情况
					if (i == 0)
					{
						if (j != 11)
						{
							if (chess[i + 4][j + 4] == BLANK)
							{
								val += 2500;
								j += 3;
								i += 3;
								continue;
							}
						}
					}
					else if (i == 13 || j == 13)
					{
						if (chess[i - 1][j - 1] == BLANK)
						{
							val += 2500;
							j += 3;
							i += 3;
							break;
						}
					}
					else if (chess[i - 1][j - 1] != BLANK)
					{
						if (chess[i + 4][j + 4] == BLANK)
						{
							val += 2500;
							j += 3;
							i += 3;
							continue;
						}
					}
					else if (chess[i + 4][j + 4] == BLANK)
					{
						val += 300000;
						j += 3;
						i += 3;
						continue;
					}
					else
					{
						val += 2500;
						j += 3;
						i += 3;
						continue;
					}
				}

				//三子
				num = 0;
				for (int x = i, y = j; x < i + 3 && y < j + 3; x++, y++)
				{
					if (chess[x][y] == now.status)
						num++;
					if (x == SIZE || y == SIZE)
						break;
				}
				if (num == 3)
				{
					//边界
					if (i == 0 || j == 0)
					{
						if (i != 12 && j != 12)
						{
							if (chess[i + 3][j + 3] == BLANK)
							{
								val += 500;
								j += 2;
								i += 2;
								continue;
							}
						}
					}
					else
					{
						if (i == 12 || j == 12)
						{
							if (chess[i - 1][j - 1] == BLANK)
							{
								val += 500;
								j += 2;
								i += 2;
								continue;
							}
						}
						else
						{
							if (chess[i - 1][j - 1] != BLANK)
							{
								if (chess[i + 3][j + 3] == BLANK)
								{
									val += 500;
									j += 2;
									i += 2;
									continue;
								}
							}
							else
							{
								//活三
								if (chess[i + 3][j + 3] == BLANK)
								{
									val += 3000;
									j += 2;
									i += 2;
									continue;
								}
								else
								{
									val += 500;
									j += 2;
									i += 2;
									continue;
								}
							}
						}
					}
					
				}
				if (i != 0 && i != 13 && j != 0 && j != 13 
					&& chess[i][j] == chess[i + 1][j + 1] && chess[i][j] != BLANK
					&& chess[i - 1][j - 1] == BLANK && chess[i + 2][j + 2] == BLANK)
				{
					val += 50;
					j += 1;
					i += 1;
				}
			}



			for (int n = 1; n < SIZE; n++)
				for (int i = 0, j = n; i < SIZE && j < SIZE; i++, j++)
					if (chess[i][j] == now.status)
					{
						num = 0;
						for (int x = i, y = j; x < i + 5 && y < j + 5; x++, y++)
						{
							if (chess[x][y] == now.status)
								num++;
							if (x == SIZE || y == SIZE)
								break;
						}
						if (num == 5)
						{
							val += 1000000;
							i += 4;
							j += 4;
							continue;
						}
						if (num == 4)
						{
							//中间缺
							if (chess[i + 2][j + 2] == BLANK)
							{
								val += 2600;
								i += 4;
								j += 4;
								continue;
							}
							else if (chess[i + 1][j + 1] == BLANK || chess[i + 3][j + 3] == BLANK)
							{
								val += 3000;
								i += 4;
								j += 4;
								continue;
							}
						}

						//四个
						num = 0;
						for (int x = i, y = j; x < i + 4 && y < j + 4; x++, y++)
						{
							if (chess[x][y] == now.status)
								num++;
							if (x == SIZE || y == SIZE)
								break;
						}
						//四子
						if (num == 4)
						{
							//边界情况
							if (j == 0 || i == 0)
							{
								if (i != 11 && j != 11)
								{
									if (chess[i + 4][j + 4] == BLANK)
									{
										val += 2500;
										j += 3;
										i += 3;
										continue;
									}
								}
							}
							else if (i == 11 || j == 11)
							{
								if (chess[i - 1][j - 1] == BLANK)
								{
									val += 2500;
									j += 3;
									i += 3;
									break;
								}
							}
							else if (chess[i - 1][j - 1] != BLANK)
							{
								if (chess[i + 4][j + 4] == BLANK)
								{
									val += 2500;
									j += 3;
									i += 3;
									continue;
								}
							}
							else if (chess[i + 4][j + 4] == BLANK)
							{
								val += 300000;
								j += 3;
								i += 3;
								continue;
							}
							else
							{
								val += 2500;
								j += 3;
								continue;
							}
						}

						//三子
						num = 0;
						for (int x = i, y = j; x < i + 3 && y < j + 3; x++, y++)
						{
							if (chess[x][y] == now.status)
								num++;
							if (x == SIZE || y == SIZE)
								break;
						}
						if (num == 3)
						{
							//边界
							if (i == 0 || j == 0)
							{
								if (i != 12 && j != 12)
								{
									if (chess[i + 3][j + 3] == BLANK)
									{
										val += 500;
										j += 2;
										i += 2;
										continue;
									}
								}
							}
							else
							{
								if (i == 12 || j == 12)
								{
									if (chess[j - 1][i - 1] == BLANK)
									{
										val += 500;
										j += 2;
										i += 2;
										continue;
									}
								}
								else
								{
									if (chess[i - 1][j - 1] != BLANK)
									{
										if (chess[i + 3][j + 3] == BLANK)
										{
											val += 500;
											j += 2;
											i += 2;
											continue;
										}
									}
									else
									{
										//活三
										if (chess[i + 3][j + 3] == BLANK)
										{
											val += 3000;
											j += 2;
											i += 2;
											continue;
										}
										else
										{
											val += 500;
											j += 2;
											i += 2;
											continue;
										}
									}
								}
							}

						}
						if (i != 0 && i != 13 && j != 0 && j != 13 
							&& chess[i][j] == chess[i + 1][j + 1] && chess[i][j] != BLANK
							&& chess[i - 1][j - 1] == BLANK && chess[i + 2][j + 2] == BLANK)
						{
							val += 50;
							j += 1;
							i += 1;
						}
					}
	return val;
}


int LigatureOnBdia(const Point now)
{
	int num, val = 0;
	for(int k = 0; k < SIZE; k ++)
		for (int i = k, j = 0; i >= 0 && j < SIZE; i--, j++)
		{
			num = 0;
			for (int x = i, y = j; x >= i - 4 && y < j + 5; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			if (num == 5)
			{
				val += 1000000;
				i -= 4;
				j += 4;
				continue;
			}
			if (num == 4)
			{
				//中间缺
				if (chess[i - 2][j + 2] == BLANK)
				{
					val += 2600;
					i -= 4;
					j += 4;
					continue;
				}
				else if (chess[i - 1][j + 1] == BLANK || chess[i - 3][j + 3] == BLANK)
				{
					val += 3000;
					i -= 4;
					j += 4;
					continue;
				}
			}

			//四个
			num = 0;
			for (int x = i, y = j; x > i - 4 && y < j + 4; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			//四子
			if (num == 4)
			{
				//边界情况
				if (j == 0)
				{
					if (i != 0)
					{
						if (chess[i - 4][j + 4] == BLANK)
						{
							val += 2500;
							j += 3;
							i -= 3;
							continue;
						}
					}
				}
				else if (i == 0)
				{
					if (chess[i + 1][j - 1] == BLANK)
					{
						val += 2500;
						j += 3;
						i -= 3;
						break;
					}
				}
				else if (chess[i + 1][j - 1] != BLANK)
				{
					if (chess[i - 4][j + 4] == BLANK)
					{
						val += 2500;
						j += 3;
						i -= 3;
						continue;
					}
				}
				else if (chess[i - 4][j + 4] == BLANK)
				{
					val += 300000;
					j += 3;
					i -= 3;
					continue;
				}
				else
				{
					val += 2500;
					j += 3;
					i -= 3;
					continue;
				}
			}

			//三子
			num = 0;
			for (int x = i, y = j; x > i - 3 && y < j + 3; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			if (num == 3)
			{
				//边界
				if (j == 0)
				{
					if (i != 0)
					{
						if (chess[i - 3][j + 3] == BLANK)
						{
							val += 500;
							j += 2;
							i -= 2;
							continue;
						}
					}
				}
				else
				{
					if (i == 0)
					{
						if (chess[i + 1][j - 1] == BLANK)
						{
							val += 500;
							j += 2;
							i -= 2;
							continue;
						}
					}
					else
					{
						if (chess[i + 1][j - 1] != BLANK)
						{
							if (chess[i - 3][j + 3] == BLANK)
							{
								val += 500;
								j += 2;
								i -= 2;
								continue;
							}
						}
						else
						{
							//活三
							if (chess[i - 3][j + 3] == BLANK)
							{
								val += 3000;
								j += 2;
								i -= 2;
								continue;
							}
							else
							{
								val += 500;
								j += 2;
								i -= 2;
								continue;
							}
						}
					}
				}

			}
			if (i != 0 && j != 0 && chess[i][j] == chess[i - 1][j + 1]
				&& chess[i][j] != BLANK
				&& chess[i + 1][j - 1] == BLANK && chess[i - 2][j + 2] == BLANK)
			{
				val += 50;
				j += 1;
				i -= 1;
			}
		}




	

	for(int n = 1; n < SIZE; n ++)
		for (int i = SIZE, j = n; i >= 0 && j < SIZE; i--, j++)
		{
			num = 0;
			for (int x = i, y = j; x >= i - 4 && y < j + 5; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			if (num == 5)
			{
				val += 1000000;
				i -= 4;
				j += 4;
				continue;
			}
			if (num == 4)
			{
				//中间缺
				if (chess[i - 2][j + 2] == BLANK)
				{
					val += 2600;
					i -= 4;
					j += 4;
					continue;
				}
				else if (chess[i - 1][j + 1] == BLANK || chess[i - 3][j + 3] == BLANK)
				{
					val += 3000;
					i -= 4;
					j += 4;
					continue;
				}
			}

			//四个
			num = 0;
			for (int x = i, y = j; x > i - 4 && y < j + 4; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			//四子
			if (num == 4)
			{
				//边界情况
				if (j == 0)
				{
					if (i != 0)
					{
						if (chess[i - 4][j + 4] == BLANK)
						{
							val += 2500;
							j += 3;
							i -= 3;
							continue;
						}
					}
				}
				else if (i == 0)
				{
					if (chess[i + 1][j - 1] == BLANK)
					{
						val += 2500;
						j += 3;
						i -= 3;
						break;
					}
				}
				else if (chess[i + 1][j - 1] != BLANK)
				{
					if (chess[i - 4][j + 4] == BLANK)
					{
						val += 2500;
						j += 3;
						i -= 3;
						continue;
					}
				}
				else if (chess[i - 4][j + 4] == BLANK)
				{
					val += 300000;
					j += 3;
					i -= 3;
					continue;
				}
				else
				{
					val += 2500;
					j += 3;
					i -= 3;
					continue;
				}
			}

			//三子
			num = 0;
			for (int x = i, y = j; x > i - 3 && y < j + 3; x--, y++)
			{
				if (chess[x][y] == now.status)
					num++;
				if (x == 0 || y == SIZE)
					break;
			}
			if (num == 3)
			{
				//边界
				if (j == 0)
				{
					if (i != 0)
					{
						if (chess[i - 3][j + 3] == BLANK)
						{
							val += 500;
							j += 2;
							i -= 2;
							continue;
						}
					}
				}
				else
				{
					if (i == 0)
					{
						if (chess[i + 1][j - 1] == BLANK)
						{
							val += 500;
							j += 2;
							i -= 2;
							continue;
						}
					}
					else
					{
						if (chess[i + 1][j - 1] != BLANK)
						{
							if (chess[i - 3][j + 3] == BLANK)
							{
								val += 500;
								j += 2;
								i -= 2;
								continue;
							}
						}
						else
						{
							//活三
							if (chess[i - 3][j + 3] == BLANK)
							{
								val += 3000;
								j += 2;
								i -= 2;
								continue;
							}
							else
							{
								val += 500;
								j += 2;
								i -= 2;
								continue;
							}
						}
					}
				}

			}
			if (i != 0 && j != 0 && chess[i][j] == chess[i - 1][j + 1]
				&& chess[i][j] != BLANK
				&& chess[i + 1][j - 1] == BLANK && chess[i - 2][j + 2] == BLANK)
			{
				val += 50;
				j += 1;
				i -= 1;
			}
		}

		return val;
}