#include <cstdio>
#define N 100005
double f[N],g[N];
int main()
{
	int n;scanf("%d",&n);
	f[0]=g[0]=0;
	double pi,ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&pi);
		f[i]=f[i-1]*pi+pi;
		g[i]=(g[i-1]+2*f[i-1])*pi+pi;
		ans+=((g[i-1]+f[i-1])*3+1)*pi;
	}
	printf("%.1lf",ans);
}