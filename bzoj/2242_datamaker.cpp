#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(NULL));
	freopen("2242.in","w",stdout);
	
	int T=20;
	printf("%d %d\n",T,3);
	for(int i=1;i<=T;i++)
		printf("%d %d %d\n",rand()%10+1,rand()%10+1,rand()%10+1);
}