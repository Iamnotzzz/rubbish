#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main() {
	int row1, col1, i1, i2, row2, col2, i,io;
	char d;
	int a[100][100],b[100][100],c[100][100];
	srand(time(0));

	do {
		printf("�Ƿ������������");
		scanf("%d", &i);

		printf("������");
		scanf("%d", &row1);
		printf("������");
		scanf("%d", &col1);
		if(i){
			int m, n;
			printf("����Ԫ��ȡֵ");
			scanf("%d %d", &n, &m);
			printf("����a\n");
			for (i1 = 1; i1 <= row1; i1++) {
				for (i2 = 1; i2 <= col1; i2++) {
					a[i1][i2]=rand()%(m-n+1);
				}

			}
		}
		else {
		
			printf("����a\n");
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

			printf("��������\n");
			getchar();
			scanf("%c", &d);

			if (d == '+' || d == '*' || d == '-') {
				//�Ӽ���
				printf("����b\n");
				printf("������");
				scanf("%d", &row2);
				printf("������");
				scanf("%d", &col2);

				printf("�Ƿ������������");
				scanf("%d", &i);

				if (i) {
					int m, n;
					printf("����Ԫ��ȡֵ");
					scanf("%d %d", &n, &m);
					printf("����b\n");
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
					printf("�޷�����");
				}
			}
			else if (d == 'T') {

				//�㵹��

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

			printf("�Ƿ������1Ϊ������0Ϊ������");
			scanf("%d", &io);
		
	}while (io != 0);

	return 0;
}