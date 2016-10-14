#include <cstdio>

int main()
{
	freopen("1305.in","w",stdout);
	printf("50 10\n");
	for(int i=1;i<=50;i++)
	{
		for(int j=1;j<=50;j++)
			putchar('Y');
		putchar('\n');
	}
}