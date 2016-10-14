#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(NULL));
	freopen("p1564.in","w",stdout);
	int n=100000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d\n",(rand()<<15)+rand()%(1<<15));
//		printf("%d\n",rand()%10+1);
}