#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>//��������ͷ�ļ�
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
 //��ʼ��Ϸ
void Start();

//���ñ���
void setbkg();

//���ð�ť
void setbutton();

//����˫�˵İ�ť
void setButtonForLocal();

//���ʻطŵİ�ť
void setButtonForPlayback();

int getchoice();
void drawBoard();

//��ʾ��ǰ����е��������ӷֲ�
void showAllpieces();

//չʾ��Ϸ����
void showRules();

//չʾ������Ϣ
void showAuthor();

//��ȡ���������
void getMou(int* x, int* y);