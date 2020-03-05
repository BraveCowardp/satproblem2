#ifndef Binary Puzzle_H
#define Binary Puzzle_H
#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#define order 4
//#define parameter "p cnf"
//#define exist 1
//#define unexist 2
//#define _false 3
//#define scanf scanf_s    //vs中为了确保数据的安全性使用scanf_s函数而不用scanf函数
//typedef int status;   //函数返回值类型定义
//int finderror = 0;
//
//typedef struct Vex {
//	int index;
//	int sig;
//	int status;
//	struct Vex* NextVexp;
//}Vex, *Vexp;
//typedef struct Vexhead {
//	int WhichLine;
//	int status;
//	int vexnum;
//	int ForWhichIndex;
//	int ForWhichSig;
//	Vexp FirstVex;
//	struct Vexhead *NextLine;
//}Vexhead, *Vexheadp;
//typedef struct {
//	int LineNum;
//	int BoolNum;
//	Vexhead *VexList;
//}ListHead, *Listheadp;
//typedef struct memory {
//	int index;
//	int sig;
//	struct memory *nextmmy;
//}Memory, *Memoryp;
//typedef struct ChooseList {
//	int index;
//	int num;
//	//int sig;
//}chooseList;
int xytonum(int x, int y);
void ruler1(FILE *fp);
void combo(int n, int k, int deep, int start);
void ruler2(int n, int k, int deep, int start, int line, FILE *fp);

void ruler3(FILE *fp);
void hash(void);
int comboNum(void);
int comboNum2(void);
void board(void);

int comboNum(void)
{
	int factorial1, factorial2, factorial3, i;
	for (i = 1, factorial1 = 1; i <= order; i++) factorial1 = factorial1 * i;
	for (i = 1, factorial2 = 1; i <= 2; i++) factorial2 = factorial2 * i;
	for (i = 1, factorial3 = 1; i <= (order - 2); i++) factorial3 = factorial3 * i;
	return factorial1 / (factorial2 * factorial3);
}
int comboNum2(void)
{
	int factorial1, factorial2, factorial3, i;
	for (i = 1, factorial1 = 1; i <= order; i++)factorial1 = factorial1 * i;
	for (i = 1, factorial2 = 1; i <= order / 2 + 1; i++)factorial2 = factorial2 * i;
	for (i = 1, factorial3 = 1; i <= order / 2 - 1; i++) factorial3 = factorial3 * i;
	return factorial1 / (factorial2*factorial3);
}
int xytonum(int x, int y)
{
	return (x - 1) * order + y;
}
void ruler1(FILE *fp)
{
	//Vexheadp p = NULL, p1 = NULL;
	//Vexp q = NULL, q1 = NULL;
	//FILE *fp;
	int i, j, three;
	//char filename[50]="./cnf/cnf_";
	//char length[3];
	int combonum = comboNum();
	int combonum2 = comboNum2();
	//_itoa(order, length, 10);
	//strcat(filename, length);
	//strcat(filename, ".cnf");
	//if ((fp = fopen(filename, "wb")) == NULL) {
	//	printf("File open error.\n");
	//	
	//}
	//else
	//{
	fprintf(fp, "p cnf %d %d\r\n", order*order + combonum * order * 2 * 2 + combonum * order * 2 + combonum * 2, (order - 2)*order * 4 + combonum2 * order * 4 + 3 * combonum*order * 4 + 3 * combonum*order * 2 + (order + 1) * combonum * 2 + combonum * 2);
	for (i = 1; i <= order; i++)
	{
		for (three = 1; three + 2 <= order; three++)
		{
			//p = (Vexheadp)malloc(sizeof(Vexhead));
			for (j = three; j <= three + 2; j++)
			{
				//printf("%d%d ", i, j);
				fprintf(fp, "%d ", (i - 1)*order + j);
				//q = (Vexp)malloc(sizeof(Vex));
				//q->index = (i - 1)*order + j;
				//q->sig = 1;
				//q->status = exist;
				//q->NextVexp = q1;
				//q1 = q;
			}
			//printf("%d\r\n", 0);
			fprintf(fp, "0\r\n");
			for (j = three; j <= three + 2; j++)
			{
				//printf("-%d%d ", i, j);
				fprintf(fp, "-%d ", (i - 1)*order + j);
			}
			//printf("%d\r\n", 0);
			fprintf(fp, "0\r\n");
			for (j = three; j <= three + 2; j++)
			{
				//printf("%d%d ", j, i);
				fprintf(fp, "%d ", (j - 1)*order + i);
			}
			//printf("%d\r\n", 0);
			fprintf(fp, "0\r\n");
			for (j = three; j <= three + 2; j++)
			{
				//printf("-%d%d ", j, i);
				fprintf(fp, "-%d ", (j - 1)*order + i);
			}
			//printf("%d\r\n", 0);
			fprintf(fp, "0\r\n");
		}

	}
	//}


}
void combo(int n, int k, int deep, int start)
{
	int i, j;
	static int *result = (int *)malloc(k * sizeof(int));
	for (i = start; i <= n - k + deep; i++)
	{
		result[deep - 1] = i;
		if (deep != k) combo(n, k, deep + 1, i + 1);
		else
		{
			for (j = 0; j < k; j++) printf("%d", result[j]);
			printf(" ");
		}
	}

}
void ruler2(int n, int k, int deep, int start, int line, FILE *fp)
{
	int i, j;
	static int *result = (int *)malloc(k * sizeof(int));
	for (i = start; i <= n - k + deep; i++)
	{
		result[deep - 1] = i;
		if (deep == k)
		{
			for (j = 0; j < k; j++)/* printf("%d%d ", line, result[j]),*/ fprintf(fp, "%d ", (line - 1)*order + result[j]);
			//printf("\n");
			fprintf(fp, "0\r\n");
			for (j = 0; j < k; j++) /*printf("-%d%d ", line, result[j]), */fprintf(fp, "-%d ", (line - 1)*order + result[j]);
			//printf("\n");
			fprintf(fp, "0\r\n");
			for (j = 0; j < k; j++)/* printf("%d%d ", result[j], line),*/ fprintf(fp, "%d ", (result[j] - 1)*order + line);
			//printf("\n");
			fprintf(fp, "0\r\n");
			for (j = 0; j < k; j++) /*printf("-%d%d ", result[j], line), */fprintf(fp, "-%d ", (result[j] - 1)*order + line);
			//printf("\n");
			fprintf(fp, "0\r\n");

		}
		else ruler2(n, k, deep + 1, i + 1, line, fp);

	}

}
void ruler3(FILE *fp)
{
	int sig1, i, j, k, sig2, k1;
	int combonum = comboNum();
	for (sig1 = 1; sig1 <= 2; sig1++)
	{
		for (i = 1; i < order; i++)
		{
			for (j = i + 1; j <= order; j++)
			{
				for (k = 1; k <= order; k++)
				{
					for (sig2 = 1; sig2 <= 2; sig2++)
					{
						if (sig1 == 1)
						{
							if (sig2 == 1)
							{
								//printf("%d%d -%d%d%d%d%d 0", i, k, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("%d%d -%d%d%d%d%d 0", j, k, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("-%d%d -%d%d %d%d%d%d%d 0", i, k, j, k, sig1, i, j, k, sig2);
								//printf("\n");
								fprintf(fp, "%d -%d 0\r\n", (i - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "%d -%d 0\r\n", (j - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "-%d -%d %d 0\r\n", (i - 1)*order + k, (j - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								//printf("%d ", sig2 + 2 * (k - 1) + ((i - 1)*(order-1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
							}
							else
							{
								//printf("-%d%d -%d%d%d%d%d 0", i, k, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("-%d%d -%d%d%d%d%d 0", j, k, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("%d%d %d%d %d%d%d%d%d 0", i, k, j, k, sig1, i, j, k, sig2);
								//printf("\n");
								fprintf(fp, "-%d -%d 0\r\n", (i - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "-%d -%d 0\r\n", (j - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "%d %d %d 0\r\n", (i - 1)*order + k, (j - 1)*order + k, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								//printf("%d\n ", sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);

							}
						}
						else
						{
							if (sig2 == 1)
							{
								//printf("%d%d -%d%d%d%d%d 0", k, i, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("%d%d -%d%d%d%d%d 0", k, j, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("-%d%d -%d%d %d%d%d%d%d 0", k, i, k, j, sig1, i, j, k, sig2);
								//printf("\n");
								fprintf(fp, "%d -%d 0\r\n", (k - 1)*order + i, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "%d -%d 0\r\n", (k - 1)*order + j, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "-%d -%d %d 0\r\n", (k - 1)*order + i, (k - 1)*order + j, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								//printf("%d ", sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);

							}
							else
							{
								//printf("-%d%d -%d%d%d%d%d 0", k, i, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("-%d%d -%d%d%d%d%d 0", k, j, sig1, i, j, k, sig2);
								//printf("\n");
								//printf("%d%d %d%d %d%d%d%d%d 0", k, i, k, j, sig1, i, j, k, sig2);
								//printf("\n");
								fprintf(fp, "-%d -%d 0\r\n", (k - 1)*order + i, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "-%d -%d 0\r\n", (k - 1)*order + j, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								fprintf(fp, "%d %d %d 0\r\n", (k - 1)*order + i, (k - 1)*order + j, order * order + sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);
								//printf("\n");
								//printf("%d\n ", sig2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2);

							}
						}
					}
					//printf("-%d%d%d%d%d %d%d%d%d 0", sig1, i, j, k, 1, sig1, i, j, k);
					//printf("\n");
					//printf("-%d%d%d%d%d %d%d%d%d 0", sig1, i, j, k, 2, sig1, i, j, k);
					//printf("\n");
					//printf("%d%d%d%d%d %d%d%d%d%d -%d%d%d%d 0", sig1, i, j, k, 1, sig1, i, j, k, 2, sig1, i, j, k);
					//printf("\n");
					//printf("%d%d%d%d %d%d%d 0", sig1, i, j, k, sig1, i, j);
					//printf("\n");
					fprintf(fp, "-%d %d 0\r\n", order * order + 1 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2, order * order + combonum * order * 2 * 2 + k + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order);
					//printf("\n");
					fprintf(fp, "-%d %d 0\r\n", order * order + 2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2, order * order + combonum * order * 2 * 2 + k + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order);
					//printf("\n");
					fprintf(fp, "%d %d -%d 0\r\n", order * order + 1 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2, order * order + 2 + 2 * (k - 1) + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1) * 2 * order + (sig1 - 1)*combonum*order * 2, order * order + combonum * order * 2 * 2 + k + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order);
					//printf("\n");
					fprintf(fp, "%d %d 0\r\n", order * order + combonum * order * 2 * 2 + k + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order, order * order + combonum * order * 2 * 2 + combonum * order * 2 + (i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i + (sig1 - 1)*combonum);
					//printf("\n");
					//printf("%d ", combonum *order * 2 * 2 + k + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order);
				}

				for (k1 = 1; k1 <= order; k1++)
				{
					fprintf(fp, "-%d ", order * order + combonum * order * 2 * 2 + k1 + ((i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i - 1)*order + (sig1 - 1)*combonum*order);
				}
				fprintf(fp, "-%d 0\r\n", order * order + combonum * order * 2 * 2 + combonum * order * 2 + (i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i + (sig1 - 1)*combonum);
				fprintf(fp, "%d 0\r\n ", order * order + combonum * order * 2 * 2 + combonum * order * 2 + (i - 1)*(order - 1) - (i - 2)*(i - 1) / 2 + j - i + (sig1 - 1)*combonum);
			}
		}
	}

}
void board(void)
{
	int i, j;
	setxy(15, 5);
	printf("┌");
	setxy(15 + 4 * order, 5);
	printf("┐");
	setxy(15, 5 + 2 * order);
	printf("└");
	setxy(15 + 4 * order, 5 + 2 * order);
	printf("┘");
	for (i = 0; i <= order; i++)
	{
		for (j = 0; j < order; j++)
		{
			setxy(15 + 2 + 4 * j, 5 + 2 * i);
			printf("─");
			setxy(15 + 4 * i, 5 + 1 + 2 * j);
			printf("│");
		}
	}
	for (i = 0; i < order - 1; i++)
	{
		setxy(15, 5 + 2 + 2 * i);
		printf("├");
		setxy(15 + 4 + 4 * i, 5);
		printf("┬");
		setxy(15 + 4 * order, 5 + 2 + 2 * i);
		printf("┤");
		setxy(15 + 4 + 4 * i, 5 + 2 * order);
		printf("┴");
	}
	for (i = 0; i < order - 1; i++)
	{
		for (j = 0; j < order - 1; j++)
		{
			setxy(15 + 4 + 4 * j, 5 + 2 + 2 * i);
			printf("┼");
		}
	}
	for (i = 1; i <= order; i++)
	{
		setxy(15 + 4 * i - 2, 4);
		printf("%d", i);
		setxy(13, 5 + 2 * i - 1);
		printf("%d", i);
	}
}
#endif // !Binary Puzzle_H
