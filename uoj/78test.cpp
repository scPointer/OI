#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

int main()
{
	freopen("p78.in","w",stdout);
	srand(time(NULL));
	printf("500 300 200000\n");
	for(int i=1;i<=200000;i++)
	{
		printf("%d %d\n",rand()%500+1,rand()%300+1);
	}
	return 0;
}
