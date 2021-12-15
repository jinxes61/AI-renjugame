#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "local_double.h"
#include "type_define.h"

#define SIZE 15

extern int chess[SIZE][SIZE];      //´¢´æÆå×Ó×´Ì¬,0:ÎªÂä×Ó,1:ºÚ,2:°×
Point playback[SIZE * SIZE];

int main() {
	int width = 640;
	int height = 480;
	initgraph(width, height);
	Start();
	
	//Point best;
	//int a = getMaxValue(&best, 4, 2, 999999999);
	return 0;
}