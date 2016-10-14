#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(NULL));
	freopen("x.in","w",stdout);
	int n=10000000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d\n",rand());
}