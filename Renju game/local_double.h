#define _CRT_SECURE_NO_WARNINGS
#include "type_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <Windows.h>

#ifndef LOCAL_BOARD_H
#define LOCAL_BOARD_H
#endif // !LOCAL_BOARD_H

#ifndef LOCAL_DOUBLE_H
#define LOCAL_DOUBLE_H
#include "board.h"
#endif // !LOCAL_DOUBLE_H




//����1�������ڴ˴����Ӳ�������ӹ��̣�����0���˴����Ӳ�����
int putdown(Point * now, int x, int y);

//��ʼ��Ϸ
void localDouble();

//չʾ���
void showResult(int winner, int num);

//�ж��Ƿ��н��(�У��У��Խ��ߣ����Խ���)
int judge(const Point now);
int judgeRow(const Point now);
int judgeLine(const Point now);
int judgeDia(const Point now);
int judgeBdia(const Point now);

//������
void showPiece(const Point now);

//������������
void setstyle();