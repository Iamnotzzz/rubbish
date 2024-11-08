#include"head.h"//这是一个定时器

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