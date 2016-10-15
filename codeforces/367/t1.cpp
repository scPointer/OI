#include <cstdio>
#include <cmath>
int main()
{
	int x0,y0;scanf("%d%d",&x0,&y0);
	int n;scanf("%d",&n);
	double ans=1e30;
	double x,y,v;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&x,&y,&v);
		double res=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0))/v;
		if(ans>res) ans=res;
	}
	printf("%.9lf",ans);
}
