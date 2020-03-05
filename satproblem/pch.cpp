// pch.cpp: 与预编译标头对应的源文件；编译成功所必需的

#include "pch.h"
void setxy(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。
