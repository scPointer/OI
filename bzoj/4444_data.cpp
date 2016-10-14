#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
	freopen("4444.in","w",stdout);
	int n=5,m=10;
	srand(time(NULL));
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",rand()%m+1,rand()%m+1);
}
