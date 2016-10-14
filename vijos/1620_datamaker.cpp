#include <cstdio>

int main()
{
	freopen("p1620.in","w",stdout);
	int n=100000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",i);
	printf("\n");
	for(int i=1;i<=n-1;i++)
		printf("%d %d\n",i,i+1);
	printf("%d\n",n+1);
	for(int i=1;i<=n/2;i++)
		printf("2 %d %d %d\n",i,i,i);
	for(int i=1;i<=n/2;i++)
		printf("1 %d %d\n",i,i+n/2);
	printf("1 1 1\n");
}
