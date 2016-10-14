#include <cstdio>
#define N 1005
double f[N][N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	f[n][m]=0;
	for(int i=n;i>=0;i--)
		for(int j=m;j>=0;j--)
		{
			if(i==n && j==m) continue;
			f[i][j]+=f[i+1][j+1]*(n-i)*(m-j);
			f[i][j]+=f[i+1][j]*(n-i)*j;
			f[i][j]+=f[i][j+1]*i*(m-j);
			f[i][j]+=n*m;
			f[i][j]/=(n*m-i*j);
		}
	printf("%.4lf\n",f[0][0]);
}