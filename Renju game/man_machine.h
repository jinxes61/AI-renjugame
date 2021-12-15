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

//��ʼ��Ϸ
void manVmachine();

//�ж��Ƿ����̫Զ
int tooFar(int x, int y);

//Ѱ��ֵ���ĵ�
value getMaxValue(int leftstep, int color, int alpha, int beta, int dep);         //��ѵ�

//��������
int evaluate(int color);
//�����ֺ���
int LigatureOnLine(const Point now);

int LigatureOnRow(const Point now);

int LigatureOnDia(const Point now);

int LigatureOnBdia(const Point now);


