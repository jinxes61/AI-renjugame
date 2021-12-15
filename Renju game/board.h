#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>//导入声音头文件
#pragma comment(lib,"Winmm.lib")
#include "type_define.h"

#ifndef BOARD_H
#define BOARD_H

#include "local_double.h"

#endif // !BOARD_H

#ifndef MVM

#define MVM
#include "man_machine.h"

#endif // !MVM


#ifndef SIZE
#define SIZE 15
#endif
 //开始游戏
void Start();

//设置背景
void setbkg();

//设置按钮
void setbutton();

//本地双人的按钮
void setButtonForLocal();

//精彩回放的按钮
void setButtonForPlayback();

int getchoice();
void drawBoard();

//显示当前棋局中的所有棋子分布
void showAllpieces();

//展示游戏规则
void showRules();

//展示作者信息
void showAuthor();

//获取鼠标点击坐标
void getMou(int* x, int* y);