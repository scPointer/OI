#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 505
#define eps 1e-7
int n,m;
struct Vector{
	double a[N];
	int cost;
	bool nozero(int p){return fabs(a[p])>eps;}
	int findfst(){for(int i=1;i<=m;i++) if(fabs(a[i])>eps) return i;return 0;}
	void calc(Vector& k,double pow){for(int i=1;i<=m;i++)a[i]-=k.a[i]*pow;}
}vc[N];
inline bool cmp(const Vector& a,const Vector& b){return a.cost<b.cost;}
int main()
{
//	freopen("4004.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&vc[i].a[j]);
	for(int i=1;i<=n;i++)
		scanf("%d",&vc[i].cost);
	std::sort(vc+1,vc+1+n,cmp);
	int ans1=0,ans2=0;
	for(int i=1,p;i<=n;i++)
		if(p=vc[i].findfst())
		{
			ans1++;ans2+=vc[i].cost;
			double vp=vc[i].a[p];
			for(int j=i+1;j<=n;j++)
				if(vc[j].nozero(p))
				{
					vc[j].calc(vc[i],vc[j].a[p]/vp);
				}
		}
	printf("%d %d",ans1,ans2);
}