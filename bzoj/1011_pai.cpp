#include <cstdio>
#include <cstdlib>
#include <ctime>
int n;
inline int rand32(){return (rand()<<15) | rand();}
int main()
{
	freopen("1011.in","w",stdout);
	srand(time(NULL));
	int n=100000;
	printf("%d 0.35\n",n);
	for(int i=1;i<=n;i++)
		printf("%d\n",rand32()%10000000);
}
