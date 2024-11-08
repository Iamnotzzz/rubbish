#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int main() {
	int row1, col1, i1, i2, row2, col2, i,io;
	char d;
	int a[100][100],b[100][100],c[100][100];
	srand(time(0));

	do {
		printf("是否生成随机矩阵");
		scanf("%d", &i);

		printf("输入行");
		scanf("%d", &row1);
		printf("输入列");
		scanf("%d", &col1);
		if(i){
			int m, n;
			printf("输入元素取值");
			scanf("%d %d", &n, &m);
			printf("输入a\n");
			for (i1 = 1; i1 <= row1; i1++) {
				for (i2 = 1; i2 <= col1; i2++) {
					a[i1][i2]=rand()%(m-n+1);
				}

			}
		}
		else {
		
			printf("输入a\n");
			for (i1 = 1; i1 <= row1; i1++) {
				for (i2 = 1; i2 <= col1; i2++) {
					scanf("%d", &a[i1][i2]);
				}

			}
		}
			printf("\n");
			for (i1 = 1; i1 <= row1; i1++) {
				for (i2 = 1; i2 <= col1; i2++) {
					printf("%d\t", a[i1][i2]);
				}
				printf("\n");
			}

			printf("定义运算\n");
			getchar();
			scanf("%c", &d);

			if (d == '+' || d == '*' || d == '-') {
				//加减乘
				printf("输入b\n");
				printf("输入行");
				scanf("%d", &row2);
				printf("输入列");
				scanf("%d", &col2);

				printf("是否生成随机矩阵");
				scanf("%d", &i);

				if (i) {
					int m, n;
					printf("输入元素取值");
					scanf("%d %d", &n, &m);
					printf("输入b\n");
					for (i1 = 1; i1 <= row2; i1++) {
						for (i2 = 1; i2 <= col2; i2++) {
							b[i1][i2] = rand() % (m - n + 1);
						}

					}
				}
				else {

					for (i1 = 1; i1 <= row2; i1++) {
						for (i2 = 1; i2 <= col2; i2++) {
							scanf("%d", &b[i1][i2]);
						}

					}
				}

				
				printf("\n");
				for (i1 = 1; i1 <= row2; i1++) {
					for (i2 = 1; i2 <= col2; i2++) {
						printf("%d\t", b[i1][i2]);
					}
					printf("\n");
				}
				printf("\n");

				if (d == '+' && row1 == row2 && col1 == col2) {
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col1; i2++) {
							a[i1][i2] += b[i1][i2];
						}

					}
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col1; i2++) {
							printf("%d\t", a[i1][i2]);
						}
						printf("\n");
					}
				}
				else if (d == '-' && row1 == row2 && col1 == col2) {
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col1; i2++) {
							a[i1][i2] -= b[i1][i2];
						}

					}
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col1; i2++) {
							printf("%d\t", a[i1][i2]);
						}
						printf("\n");
					}

				}
				else if (row2 == col1 && d == '*') {
					int s;
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col2; i2++) {
							c[i1][i2] = 0;
						}

					}

					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col2; i2++) {
							for (s = 1; s <= row2; s++) {
								c[i1][i2] += a[i1][s] * b[s][i2];
							}
						}

					}
					for (i1 = 1; i1 <= row1; i1++) {
						for (i2 = 1; i2 <= col2; i2++) {
							printf("%d\t", c[i1][i2]);
						}
						printf("\n");
					}
				}
				else {
					printf("无法计算");
				}
			}
			else if (d == 'T') {

				//算倒置

				for (i1 = 1; i1 <= row1; i1++) {
					for (i2 = 1; i2 <= row1; i2++) {
						c[i2][i1] = a[i1][i2];
					}
				}



				for (i1 = 1; i1 <= row1; i1++) {
					for (i2 = 1; i2 <= col1; i2++) {
						printf("%d\t", c[i1][i2]);
					}
					printf("\n");
				}
			}

			printf("是否继续（1为继续，0为结束）");
			scanf("%d", &io);
		
	}while (io != 0);

	return 0;
}