#include <cstdio>

int main()
{
	int n;scanf("%d",&n);
	printf("I hate");
	while(--n)
	{
		printf(" that I love");
		if(--n==0) break;
		printf(" that I hate");
	}
	printf(" it");
}
