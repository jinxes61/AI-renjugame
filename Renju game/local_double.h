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




//返回1：可以在此处落子并完成落子过程；返回0：此处有子并提醒
int putdown(Point * now, int x, int y);

//开始游戏
void localDouble();

//展示结果
void showResult(int winner, int num);

//判断是否有结果(行，列，对角线，反对角线)
int judge(const Point now);
int judgeRow(const Point now);
int judgeLine(const Point now);
int judgeDia(const Point now);
int judgeBdia(const Point now);

//画棋子
void showPiece(const Point now);

//设置文字类型
void setstyle();