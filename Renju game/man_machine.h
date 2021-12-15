#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include "type_define.h"

#ifndef MAN_MACHINE_H

#define MAN_MACHINE_H
#include "board.h"

#endif // !MAN_MACHINE_H

#define SIZE 15
#define inf 1e9

extern int chess[SIZE][SIZE];

//开始游戏
void manVmachine();

//判断是否距离太远
int tooFar(int x, int y);

//寻找值最大的点
value getMaxValue(int leftstep, int color, int alpha, int beta, int dep);         //最佳点

//评估函数
int evaluate(int color);
//评估分函数
int LigatureOnLine(const Point now);

int LigatureOnRow(const Point now);

int LigatureOnDia(const Point now);

int LigatureOnBdia(const Point now);


