#include <cstdio>
#define N 1005
#define INF 5000000
#define eps 1e-9
double a[N][N],b[N][N],c[N][N];
double f[N][N];
int main()
{
	int n,m; 
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%lf%lf%lf",&a[i][j],&b[i][j],&c[i][j]);
		f[n][m]=0;
		for(int i=n;i>=1;i--)
			for(int j=m;j>=1;j--)
				if(i==n && j==m) continue;
				else if(1-a[i][j]<eps) continue;
				else f[i][j]=(f[i][j+1]*b[i][j]+f[i+1][j]*c[i][j]+1)/(1-a[i][j]);
		printf("%.3lf\n",f[1][1]*2);
	}
}