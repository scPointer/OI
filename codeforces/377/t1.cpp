#include <cstdio>

int main()
{
	int n;scanf("%d",&n);
	int k;scanf("%d",&k);
	for(int i=1;;i++)
	{
		if(i*n%10==k || i*n%10==0)
		{
			printf("%d",i);
			break;
		}
	}
}
