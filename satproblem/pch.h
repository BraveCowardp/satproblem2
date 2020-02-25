

#ifndef PCH_H
#define PCH_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define parameter "p cnf"
#define exist 1
#define unexist 2
#define _false 3
#define scanf scanf_s    //vs中为了确保数据的安全性使用scanf_s函数而不用scanf函数
typedef int status;   //函数返回值类型定义
int finderror = 0;

typedef struct Vex {
	int index;
	int sig;
	int status;
	struct Vex* NextVexp;
}Vex, *Vexp;
typedef struct Vexhead {
	int WhichLine;
	int status;
	int vexnum;
	int ForWhichIndex;
	int ForWhichSig;
	Vexp FirstVex;
	struct Vexhead *NextLine;
}Vexhead, *Vexheadp;
typedef struct {
	int LineNum;
	int BoolNum;
	Vexhead *VexList;
}ListHead, *Listheadp;
typedef struct memory {
	int index;
	int sig;
	struct memory *nextmmy;
}Memory, *Memoryp;
typedef struct ChooseList {
	int index;
	int num;
	//int sig;
}chooseList;
extern int *IndexList;
extern int IndexListp;
extern chooseList* Choose;
extern int choosep;

#endif //PCH_H
