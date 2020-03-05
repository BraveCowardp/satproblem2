
#include "pch.h"
#include "dpll.h"
#include "Binary Puzzle.h"


void InitiIndexList(Listheadp L);
void Cnfsolve(Listheadp L, char filename[]);
char* BinaryPuzzle(void);
void Putxy(int x, int y, int sig);
void DigIndex(Listheadp L,char filename[]);
void AutoSolve(Listheadp L, char filename[]);
void DestoryListhead(Listheadp L);
void RandomCreat(Listheadp L, char filename[]);
void SelfSolve(int x, int y, int sig);

int order;
int *IndexList;
int *IndexList2;
int *IndexList3;
int IndexListp;
chooseList* Choose = NULL;
int choosep;
int main()
{
	char filename[150];
	int choosei, choice = -1, i, j, sig, tempsig, k, flag;
	Listheadp L = NULL;
	while (true)
	{
		system("cls");
		setxy(15, 5);
		printf("请输入你要进行的操作:");
		setxy(17, 7);
		printf("1.dpll解决sat问题");
		setxy(17, 8);
		printf("2.二进制数独游戏");
		setxy(17, 9);
		printf("0.退出");
		do
		{
			setxy(36, 5);
			scanf("%d", &choice);
			setxy(36, 5);
			printf(" ");
		} while (choice != 0 && choice != 1 && choice != 2);
		switch (choice)
		{
		case 0:
			setxy(0, 5 + 10 + 2 * order);
			printf("\n\n\n\n\n\n");
			return 0;
			break;
		case 1:
			system("cls");
			setxy(15, 5);
			printf("请输入同目录下cnf文件(包括扩展名):");
			setxy(15, 6);
			scanf("%s", filename, 150);
			setxy(15, 7);
			L = (Listheadp)malloc(sizeof(ListHead));
			CnfRead(filename, L);
			IndexList = (int*)malloc(L->BoolNum * sizeof(int));
			for (IndexListp = 0; IndexListp < L->BoolNum; IndexListp++) *(IndexList + IndexListp) = 0;
			IndexListp = 0;
			InitiIndexList(L);
			IndexSort(L);
			Cnfsolve(L, filename);
			getchar();
			getchar();
			break;
		case 2:

			system("cls");
			setxy(15, 5);
			order = 0;
			printf("请输入阶数(大于2的偶数):");
			while (order <= 2 || order % 2 != 0)
			{
				setxy(39, 5);
				printf("                                             ");
				setxy(39, 5);
				scanf("%d", &order);

			}
		recreat:
			system("cls");
			board();

			setxy(15 + 4 + 4 * order, 6);

			strcpy(filename, BinaryPuzzle());
			DestoryListhead(L);
			L = (Listheadp)malloc(sizeof(ListHead));
			CnfRead(filename, L);
			IndexList = (int*)malloc(L->BoolNum * sizeof(int));
			for (IndexListp = 0; IndexListp < L->BoolNum; IndexListp++) *(IndexList + IndexListp) = 0;
			IndexList3 = (int*)malloc(order * order * sizeof(int));
			for (IndexListp = 0; IndexListp < order*order; IndexListp++) *(IndexList3 + IndexListp) = 0;
			IndexListp = 0;
			InitiIndexList(L);
			IndexSort(L);
			//dpll(L->VexList, 0, 0);
			RandomCreat(L, filename);
			DigIndex(L, filename);

			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_GREEN |	FOREGROUND_BLUE);

			for (i = 1; i <= order; i++)
			{
				for (j = 1; j <= order; j++)
				{
					if (*(IndexList2 + (i - 1)*order + j - 1) == 1)
					{
						sig = 1;
						Putxy(j, i, sig);
					}
					else if (*(IndexList2 + (i - 1)*order + j - 1) == -1)
					{
						sig = 0;
						Putxy(j, i, sig);
					}

				}
			}
			AutoSolve(L, filename);
			board();
			setxy(15 + 4 + 4 * order, 6);
			printf("请输入(行 列 0/1):");
			setxy(15 + 4 + 4 * order, 7);
			printf("输入0 0 0以自动填补");
			setxy(15 + 4 + 4 * order, 8);
			printf("输入0 0 1以重新生成");
			setxy(15 + 22 + 4 * order, 6);
			while (true)
			{
				setxy(15 + 22 + 4 * order, 6);
				scanf("%d %d %d", &i, &j, &sig);
				setxy(15 + 22 + 4 * order, 6);
				printf("                                                                    ");
				setxy(15 + 22 + 4 * order, 6);
				tempsig = 0;
				flag = 0;
				if (i <= order && i >= 1 && j <= order && j >= 1 && sig >= 0 && sig <= 1)
				{

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
					SelfSolve(i, j, sig);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

					for (k = 0; k < order*order; k++)
					{
						//printf("%d ", *(IndexList2 + k));
						if (*(IndexList2 + k) == 0 && ++flag&&*(IndexList3 + k) == *(IndexList + k))
						{
							++tempsig;
						}
					}
					if (tempsig == flag)
					{
						setxy(15 + 22 + 4 * order, 6);
						printf("恭喜完成!按任意键继续");
						getchar();
						getchar();
						break;
					}
				}
				else if (i == 0 && j == 0 && sig == 0)
				{
					board();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);

					for (i = 1; i <= order; i++)
					{
						for (j = 1; j <= order; j++)
						{
							if (*(IndexList + (i - 1)*order + j - 1) == 1 && *(IndexList2 + (i - 1)*order + j - 1) == 0)
							{
								Sleep(50);
								sig = 1;
								Putxy(j, i, sig);
								//setxy(15 + 22 + 4 * order, 6);
							}
							else if (*(IndexList + (i - 1)*order + j - 1) == -1 && *(IndexList2 + (i - 1)*order + j - 1) == 0)
							{
								Sleep(50);
								sig = 0;
								Putxy(j, i, sig);
								//setxy(15 + 22 + 4 * order, 6);
							}

						}
					}

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					board();
					setxy(15 + 22 + 4 * order, 6);
					printf("按任意键继续");
					getchar();
					getchar();
					break;
				}
				else if (i == 0 && j == 0 && sig == 1)
				{
					goto recreat;
				}
			}




			//Cnfsolve(L, filename);
			break;
		}

	}



	//Listheadp L = (Listheadp)malloc(sizeof(ListHead));
	//CnfRead(filename, L);
	//IndexList = (int*)malloc(L->BoolNum * sizeof(int));
	//for (IndexListp = 0; IndexListp < L->BoolNum; IndexListp++) *(IndexList + IndexListp) = 0;
	//IndexListp = 0;
	//InitiIndexList(L);
	//IndexSort(L);
	//Cnfsolve(L, filename);
	getchar();
	getchar();
	setxy(0, 5 + 10 + 2 * order);
	printf("\n\n\n\n\n\n");
	return 0;
}
void SelfSolve(int x,int y,int sig)
{
	int index;
	index = (x - 1)*order + y;
	if (*(IndexList2 + index - 1) == 0)
	{
		Putxy(y, x, sig);
		if(sig==1) *(IndexList3 + index - 1) = sig;
		else if(sig==0) *(IndexList3 + index - 1) = -1;
	}
}
void RandomCreat(Listheadp L, char filename[])
{
	int i;
	
	{
		
		DestoryListhead(L);
		//printf("ok");
		CnfRead(filename, L);
		for (i = 0; i < L->BoolNum; i++)
		{
			*(IndexList + i) = 0;
		}
		
		for (i = 0; i < 4; i++)
		{
			srand((unsigned)time(NULL));
			if (rand() % 2 == 1) *(IndexList + rand() % (order*order)) = 1;
			else *(IndexList + rand() % (order*order)) = -1;

		}
	} while (dpll(L->VexList, 0, 0) == false);
	
}
void AutoSolve(Listheadp L, char filename[])
{
	int i, j, sig;
	CnfRead(filename, L);
	for (IndexListp = 0; IndexListp < L->BoolNum; IndexListp++) *(IndexList + IndexListp) = *(IndexList2 + IndexListp);
	//for (IndexListp = 0; IndexListp < L->BoolNum; IndexListp++) *(IndexList2 + IndexListp) = 0;
	IndexListp = 0;
	InitiIndexList(L);
	IndexSort(L);
	dpll(L->VexList, 0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);

	//for (i = 1; i <= order; i++)
	//{
	//	for (j = 1; j <= order; j++)
	//	{
	//		if (*(IndexList + (i - 1)*order + j - 1) == 1 && *(IndexList2 + (i - 1)*order + j - 1) == 0)
	//		{
	//			sig = 1;
	//			Putxy(j, i, sig);
	//		}
	//		else if (*(IndexList + (i - 1)*order + j - 1) == -1 && *(IndexList2 + (i - 1)*order + j - 1) == 0)
	//		{
	//			sig = 0;
	//			Putxy(j, i, sig);
	//		}

	//	}
	//}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void DigIndex(Listheadp L,char filename[])
{
	int i,j,tempsig ,pick, temp;
	int *randlist = (int *)malloc(order*order * sizeof(int));
	srand((unsigned)time(NULL));
	for (i = 0; i < order*order; i++)
	{
		randlist[i] = i + 1;
	}
	for (i = 0; i < order*order; i++)
	{
		pick = rand() % (order*order - i) + i;
		temp = randlist[i];
		randlist[i] = randlist[pick];
		randlist[pick] = temp;
	}
	//setxy(0, 0);
	//for (i = 0; i < order*order; i++) printf("%d ", randlist[i]);
	IndexList2 = (int *)malloc(L->BoolNum * sizeof(int));
	for (i = 0; i < L->BoolNum; i++)
	{
		*(IndexList2 + i) = 0;
	}
	for (i = 0; i < order*order; i++)
	{
		*(IndexList2 + i) = *(IndexList + i);
	}
	for (i = 0; i < order*order; i++)
	{
		tempsig = *(IndexList2 + randlist[i]);
		*(IndexList2 + randlist[i]) = -1 * tempsig;
		//setxy(3, i);
		//printf("%d", *(IndexList2 + i));
		for (j = 0; j < L->BoolNum; j++)
		{
			*(IndexList + j) = *(IndexList2 + j);

		}
		DestoryListhead(L);
		CnfRead(filename, L);
		if (dpll(L->VexList, 0, 0)) *(IndexList2 + randlist[i]) = tempsig;
		else *(IndexList2 + randlist[i]) = 0;

		//setxy(0, i);
		//printf("%d", *(IndexList2 + i));
	}
}
void DestoryListhead(Listheadp L)
{
	Vexheadp p,p1;
	Vexp q,q1;
	if (L != NULL)
	{
		for (p = L->VexList; p != NULL;)
		{
			for (q = p->FirstVex; q != NULL; )
			{
				q1 = q->NextVexp;
				free(q);
				q = q1;
			}
			p1 = p->NextLine;
			free(p);
			p = p1;
		}
		//free(L);
	}
	//L = NULL;
}
void Putxy(int x, int y, int sig)
{
	setxy(15 + 4 * x - 2, 5 + 2 * y - 1);
	printf("%d", sig);
}
char* BinaryPuzzle(void)
{
	int index, line;
	FILE *fp;
	int i, j, three;
	char filename[50] = "cnf_";
	char length[3];
	int combonum = comboNum();
	int combonum2 = comboNum2();

	_itoa(order, length, 10);
	strcat(filename, length);
	strcat(filename, ".cnf");
	if ((fp = fopen(filename, "r")) == NULL)
	{
		if ((fp = fopen(filename, "wb")) == NULL) {
			printf("File open error.\n");

		}
		else
		{
			ruler1(fp);
				for (line = 1; line <= order; line++) ruler2(order, order / 2 + 1, 1, 1, line, fp);
				ruler3(fp);
		}
		
	}
	fclose(fp);
	return filename;
}
void InitiIndexList(Listheadp L)
{
	Vexheadp p;
	Vexp q;
	int i,choosei;
	p = L->VexList;
	Choose = (chooseList*)malloc(L->BoolNum * sizeof(chooseList));
	for (choosei = 0; choosei < L->BoolNum; choosei++)
	{
		(Choose + choosei)->index = choosei + 1;
		(Choose + choosei)->num = 0;

	}
	for (i = 0; i < L->LineNum; i++)
	{
		q = p->FirstVex;
		while (true)
		{
			//printf("%d\t", q->index * q->sig);
			if (q->sig == 1) (Choose + q->index - 1)->num++;

			q = q->NextVexp;
			if (!q) break;
		}
		//printf("\n");
		p = p->NextLine;
	}
}
void Cnfsolve(Listheadp L, char filename[])
{
	bool status;
	clock_t start, end;
	setxy(15, 7);
	start = clock();
	if (status = dpll(L->VexList, 0, 0))
	{
		printf("有解\n");
	}
	else
	{
		printf("无解\n");
	}
	end = clock();
	setxy(15, 8);
	printf("time=%ldms\n", end - start);

	SaveResult(filename, L, end - start, status);
}













//李世铭 2020.2.26