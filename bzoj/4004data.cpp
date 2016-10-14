#include <cstdio>
#include <ctime>
#include <cstdlib>
int main()
{
	srand(time(NULL));
/*	freopen("4004.in","w",stdout);
	int n=10;
	int m=10;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
	{
		for(int i=1;i<=m;i++)
			printf("%d ",rand()%2);
		puts("");
	}
	for(int i=1;i<=n;i++)
		printf("%d  ",rand()%100);
		*/
	freopen("3105.in","w",stdout);
	int k=100;
	printf("%d\n",k);
	for(int i=1;i<=k;i++)
		printf("%d\n",(rand()<<15)+rand()%(1<<15));
}