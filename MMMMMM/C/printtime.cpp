#include"head.h"

void printtime()
{
	int n;
	int m;
	char s1[51];
	char s2[60];
	char s3[51] = {'0'};
	for (n = order_count-1,m=0;m<20 ; m++,n--)
	{
		if (n >= 0)
		{
			settextcolor(RED);
			settextstyle(25, 0, _T("Consolas"));
			if ((strcmp(finallytype[n], s3) != 0))
			{
				if (booltime[n] == 0)
				{
					sprintf(s1, "%d: %s: FAIL", n + 1, finallytype[n]);
					outtextxy(30, 180 + m * 30, s1);
				}
				else 
				{
					if (finallytime[n] != 0)
					{
						int hour, minute, second;
						seconds_to_time(finallytime[n], &hour, &minute, &second);
						sprintf(s2, "%d: %s: %02d:%02d:%02d", n + 1, finallytype[n], hour, minute, second);
						outtextxy(30, 180 + m * 30, s2);
					}
					else
					{
						sprintf(s2, "%d: %s: ÖÆ×÷ÖÐ", n + 1, finallytype[n]);
						outtextxy(30, 180 + m * 30, s2);
					}
				}

			}
		}
		
		
	}
}