#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
int main()
{
	freopen("p79.in","w",stdout);
	srand(time(NULL));
	printf("100 500\n");
	for(int i=1;i<=500;i++)
		printf("%d %d\n",rand()%100+1,rand()%100+1);
}
