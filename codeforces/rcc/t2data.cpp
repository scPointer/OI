#include <cstdio>
#include <ctime>
#include <cstdlib>
int rd32(){return (rand()<<15)|rand();}
int main()
{
	srand(time(NULL));
	freopen("t2.in","w",stdout);
	int n=10000;
	int m=15000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;i++)
		printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%m+1);
}