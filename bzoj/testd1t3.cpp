#include <cstdio>
#define N 52
#define CLEN 105
char mtx[N][N][CLEN];
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n; scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%s",mtx[i][j]);
		
	}
}