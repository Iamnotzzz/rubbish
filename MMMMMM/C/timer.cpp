#include"head.h"//����һ����ʱ��

int timer(int fast, int id)
{
	static int starttime[10];
	int endtime = clock();
	if (endtime - starttime[id] > fast)
	{
		starttime[id] = endtime;
		return 1;
	}
	return 0;
}