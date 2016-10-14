#include <cstdio>
int main()
{
	bool ok=1;
	int save=0,money=0;
	for(int i=1;i<=12;i++)
	{
		int ys;
		scanf("%d",&ys);
		money=money+300-ys;
		if(money<0)
		{
			printf("-%d",i);
			ok=0;
			break;
		}
		else
		{
			save+=money/100*100;
			money%=100;
		}
	}
	if(ok==1)
		printf("%d",(int)(money+save*1.2+1e-5));
	return 0;
}
