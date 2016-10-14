#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
int main()
{
	srand(time(NULL));
	freopen("4003.in","w",stdout);
	int n=10;
	int m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%100);
	puts("");
	for(int i=2;i<=n;i++)
	{
		printf("%d ",rand()%(i-1)+1);
		int tp=rand()%2;
		if(tp==0)
			printf("0 %d\n",rand()%20-10);
		else
			printf("1 %d\n",rand()%4+1);
	}
	for(int i=1;i<=m;i++)
		printf("%d %d\n",rand()%100,rand()%n+1);
}