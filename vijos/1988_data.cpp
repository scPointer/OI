#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
	freopen("p1988.in","w",stdout);
	int n=10;
	srand(time(NULL));
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d\n",rand()%20);
}
