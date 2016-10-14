#include <cstdio>
int main()
{
	int k;
	scanf("%d",&k);
	long double lim=k*1.0,sum=0;
	for(int i=1;;i++)
	{
		sum+=1/(long double)i;
		if(sum-1e-10>lim)
		{
			printf("%d",i);
			break;
		}
	}
	return 0;
}
