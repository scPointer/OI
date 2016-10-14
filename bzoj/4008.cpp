#include <cstdio>
#include <cstring>
#include <cmath>
#define N 235
long double f[N][N];
long double pp[N][N];
long double val[N];
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));
		int n,round;
		scanf("%d%d",&n,&round);
		double psb,pv;
		for(int j=2;j<=round;j++)
			pp[0][j]=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&psb,&pv);
			val[i]=pv;
			pp[i][1]=psb;
//			for(int j=2;j<=round;j++)
//				pp[i][j]=pp[i][j-1]*pp[i][1];
		}
		long double ans=0;
		f[0][round]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=round;j++)
			{
                f[i][j]=f[i-1][j]*pow(1-pp[i-1][1],j)+f[i-1][j+1]*(1-pow(1-pp[i-1][1],j+1));
                ans+=f[i][j]*(1-pow(1-pp[i][1],j))*val[i];
			}
		printf("%.10lf\n",(double)ans);
	}
}
