#include <cstdio>
int main()
{
	int u=0,ud=0;
	for(int i=1;i<=7;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a+b>=8&&a+b>u)
		{
			u=a+b;
			ud=i;
		}
	}
	printf("%d",ud);
	return 0;
}
