#include <cstdio>
#include <cstdlib>
#include <ctime>
int rand32(){return (rand()<<15)+rand()%(1<<15);}
int main()
{
	srand(time(NULL));
	freopen("p2828.in","w",stdout);
	int T=20;
	for(int i=1;i<=T;i++)
	{
		int n=200000;
		printf("%d\n",n);
		for(int i=1;i<=n;i++)
			printf("%d %d\n",rand32()%n,rand32());
	}
}