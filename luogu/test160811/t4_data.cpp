#include <cstdio>
#include <ctime>
#include <cstdlib>
int main()
{
	srand(time(NULL));
	freopen("t4.in","w",stdout);
	int n=1000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d %d %d\n",i,rand(),rand(),rand());
}
