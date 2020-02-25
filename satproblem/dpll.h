

#ifndef DPLL_H
#define DPLL_H
#include"pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool dpll(Vexheadp p, int index, int indexsig);
int IfExistSingleVex(Vexheadp p, int &sig);
void Simplify(Vexheadp p, int IfSingleIndex, int sig);
void Recover(Vexheadp p, Memoryp mmy);
int IfEmpty(Vexheadp p);
void PutOut(Vexheadp p);
void FreeMemory(Memoryp mmy);
void SaveResult(char filename[], Listheadp L, long time);
void CnfRead(char filename[], Listheadp L)
{
	FILE *fp;
	int i,j,k, bool_num, line_num, TempIndex;
	char ch;
	char readline[200];
	bool IfPCnf = false;
	Vexheadp p, p1;
	Vexp q, q1;
	if ((fp = fopen(filename, "rb")) == NULL) {
		printf("File open error.\n");
	}
	else
	{
		while (!feof(fp))
		{
			for (i = 0; i < 199; i++)
			{
				fread(&ch, sizeof(char), 1, fp);

				if (ch != '\r') readline[i] = ch;
				else i--;
				if (readline[i] == '\n')
				{
					i++;
					break;
				}

			}
			readline[i] = '\0';
			if (IfPCnf && j <= L->LineNum)
			{
				p = (Vexheadp)malloc(sizeof(Vexhead));
				p->WhichLine = j++;
				p->status = exist;
				p->vexnum = 0;
				p->NextLine = NULL;
				k = 0;
				while (true)
				{
					TempIndex = atoi(readline + k);
					if (TempIndex == 0) break;
					q = (Vexp)malloc(sizeof(Vex));
					q->status = exist;
					q->NextVexp = NULL;
					p->vexnum++;
					if (TempIndex < 0)
					{
						q->index = -TempIndex;
						q->sig = -1;
					}
					else
					{
						q->index = TempIndex;
						q->sig = 1;
					}
					if (k != 0)q1->NextVexp = q;
					else p->FirstVex = q;
					q->NextVexp = NULL;
					q1 = q;
					while (true)
					{
						k++;
						if (readline[k] == ' ') break;
					}
				}
				if (p->WhichLine != 1)p1->NextLine = p;
				else L->VexList = p;
				p->NextLine = NULL;
				p1 = p;

			}
			if (!strncmp(parameter, readline, 5))
			{
				bool_num = atoi(readline + 5);
				for (j = 0; readline[6 + j] != ' '; j++);
				line_num = atoi(readline + 6 + j);
				IfPCnf = true;
				j = 1;
				L->BoolNum = bool_num;
				L->LineNum = line_num;

			}

		}
	}
	fclose(fp);
}

bool dpll(Vexheadp p, int index, int indexsig)
{
	int IfSingleIndex;
	int sig;
	int i = 0, j = 0;
	Memoryp mmy = NULL, mmy1 = NULL;
	if (index != 0)
	{
		IfSingleIndex = index;
		sig = indexsig;
		mmy = (Memoryp)malloc(sizeof(Memory));
		mmy->index = IfSingleIndex;
		mmy->sig = sig;
		mmy->nextmmy = mmy1;
		mmy1 = mmy;
		*(IndexList + IfSingleIndex - 1) = sig;
		//printf("index:%d sig:%d i:%d\t", IfSingleIndex, sig, i);
		Simplify(p, IfSingleIndex, sig);
		//PutOut(p);
		//printf("\n\n");
		if (IfEmpty(p) == 1) return true;
		else if (IfEmpty(p) == 3)
		{

			Recover(p, mmy);
			//PutOut(p);
			//printf("\n\n");
			FreeMemory(mmy);
			return false;
		}
	}


	while (IfSingleIndex = IfExistSingleVex(p, sig))
	{

		//printf("index:%d sig:%d i:%d\t", IfSingleIndex, sig, i);
		//PutOut(p);
		//printf("\n\n")
		if (IfSingleIndex == 0) break;
		mmy = (Memoryp)malloc(sizeof(Memory));
		mmy->index = IfSingleIndex;
		mmy->sig = sig;
		mmy->nextmmy = mmy1;
		mmy1 = mmy;

		*(IndexList + IfSingleIndex - 1) = sig;
		//printf("index:%d sig:%d i:%d\t", IfSingleIndex, sig, i);
		Simplify(p, IfSingleIndex, sig);
		//PutOut(p);
		//printf("\n\n");
		if (IfEmpty(p) == 1) return true;
		else if (IfEmpty(p) == 3)
		{

			Recover(p, mmy);
			//PutOut(p);
			//printf("\n\n");
			FreeMemory(mmy);
			return false;
		}

	}
	//for (; *(IndexList + j) != 0; j++);
	for (; *(IndexList + (Choose + j)->index - 1) != 0; j++);

	index = (Choose + j)->index;
	sig = 1;
	*(IndexList + (Choose + j)->index - 1) = sig;
	if (dpll(p, index, sig)) return true;
	sig = -1;
	*(IndexList + (Choose + j)->index - 1) = sig;
	if (dpll(p, index, sig)) return true;
	Recover(p, mmy);
	//PutOut(p);
	//printf("\n\n");
	FreeMemory(mmy);
	return false;
}
int IfExistSingleVex(Vexheadp p, int &sig)
{
	Vexp q;
	for (; p != NULL; p = p->NextLine)
		if (p->status == exist && p->vexnum == 1)
		{
			for (q = p->FirstVex; q != NULL; q = q->NextVexp)
				if (q->status == exist)
				{
					sig = q->sig;
					return q->index;
				}
		}
	return 0;
}
void Simplify(Vexheadp p, int IfSingleIndex, int sig)
{
	Vexp q;
	for (; p != NULL; p = p->NextLine)
	{
		if (p->status == exist)
		{
			for (q = p->FirstVex; q != NULL; q = q->NextVexp)
			{
				if (q->status == exist && q->index == IfSingleIndex && q->sig == sig)
				{
					p->status = unexist;
					p->ForWhichIndex = IfSingleIndex;
					p->ForWhichSig = sig;

				}

			}

		}
		if (p->status == exist)
		{
			for (q = p->FirstVex; q != NULL; q = q->NextVexp)
			{
				if (q->status == exist && q->index == IfSingleIndex && q->sig == -sig)
				{
					q->status = unexist;
					p->vexnum--;
				}

			}

		}

	}
}
void Recover(Vexheadp p, Memoryp mmy)
{
	Vexheadp p1;
	Vexp q;
	for (; mmy != NULL; mmy = mmy->nextmmy)
	{
		for (p1 = p; p1 != NULL; p1 = p1->NextLine)
		{
			if (p1->status == exist)
			{
				for (q = p1->FirstVex; q != NULL; q = q->NextVexp)
					if (q->status == unexist && q->index == mmy->index && q->sig == -mmy->sig)
					{
						q->status = exist;
						p1->vexnum++;
					}
			}
			if (p1->status == unexist && p1->ForWhichIndex == mmy->index && p1->ForWhichSig == mmy->sig) p1->status = exist;

		}
		*(IndexList + mmy->index - 1) = 0;
	}
}
int IfEmpty(Vexheadp p)
{
	int sign = 0;
	for (; p != NULL; p = p->NextLine)
	{
		if (p->status == exist)
		{
			if (p->vexnum == 0)
			{
				//printf("finderror3!");
				return 3;
			}
			else
			{
				sign = 1;
			}
		}
	}
	if (sign == 0)return 1;
	else return 2;
}
void PutOut(Vexheadp p)
{
	int i;
	Vexp q;
	for (; p != NULL; )
	{
		q = p->FirstVex;
		while (p->status == exist)
		{
			if (q->status == exist)printf("%d\t", q->index * q->sig);
			q = q->NextVexp;
			if (!q) break;
			if (p->vexnum == 0) printf("finderror!");
		}
		if (p->status == exist) printf("\n");
		p = p->NextLine;
	}
}
void FreeMemory(Memoryp mmy)
{
	Memoryp mmy1;
	for (; mmy != NULL;)
	{
		mmy1 = mmy;
		mmy = mmy->nextmmy;
		free(mmy1);
	}
}
void SaveResult(char filename[], Listheadp L, long time)
{
	FILE *fp;
	int i = 0;
	char road[100] = "./result/";
	strcat(road, filename);
	strcat(road, ".res");
	if ((fp = fopen(road, "wb+")) == NULL) {
		printf("SaveResult file open error.\n");
	}
	else
	{
		fprintf(fp, "time:%ldms\r\n", time);
		while (i < L->BoolNum)
		{
			fprintf(fp, "%d:%d\t", i + 1, *(IndexList + i));
			i++;
			if (i % 6 == 0) fprintf(fp, "\r\n");
		}

		fclose(fp);
	}
}

#endif // !DPLL_H
