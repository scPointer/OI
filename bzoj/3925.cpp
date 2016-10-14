#include <cstdio>
#include <iostream>
using namespace std;
#define N 12
#define BTS 2049
#define Max(a,b) (a>b?a:b)
#define lowbit(x) (x&(-x))
#define lf long long//long double
struct poly{
	int d;
	lf a[101];
	poly(){d=0;for(int i=0;i<=100;i++) a[i]=0;}
	void operator +=(const poly& x)
	{
		d=Max(d,x.d);
		for(int i=0;i<=d;i++) a[i]+=x.a[i];
	}
	void operator =(const poly& x)
	{
		for(int i=0;i<=x.d;i++) a[i]=x.a[i];
		for(int i=x.d+1;i<=d;i++) a[i]=0;
		d=x.d;
	}
	friend poly operator *(const poly& x,const poly& y)
	{
		poly z;z.d=x.d+y.d;
		for(int i=0;i<=x.d;i++)
			for(int j=0;j<=y.d;j++)
				z.a[i+j]+=x.a[i]*y.a[j];
		return z;
	}
	friend poly operator -(poly& x,poly& y)
	{
		poly z;z.d=Max(x.d,y.d);
		for(int i=0;i<=z.d;i++) z.a[i]=x.a[i]-y.a[i];
		return z;
	}
};
void pr(poly& x)
{
//	printf("%d\n",i);
	for(int i=0;i<=x.d;i++) printf("%lf\n",(double)x.a[i]);
	cout<<endl;
}
int c[BTS][BTS];
int dp[BTS][BTS];
poly f[BTS],g[60];
int n,m;
int main()
{
	freopen("3925.txt","r",stdin);
//	freopen("3925.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,p1,p2;i<=m;i++)
	{
		scanf("%d%d",&p1,&p2);
		c[1<<(p1-1)][1<<(p2-1)]=c[1<<(p2-1)][1<<(p1-1)]=1;
	}
	for(int i=1;i<(1<<n);i++)
		for(int j=1;j<(1<<n);j++)
			if((i&j)==0)
			dp[i][j]=dp[i-lowbit(i)][j]+dp[i][j-lowbit(j)]-dp[i-lowbit(i)][j-lowbit(j)]+c[lowbit(i)][lowbit(j)];
	g[0].a[0]=1;g[1].d=1;g[1].a[0]=1;g[1].a[1]=-1;
	for(int i=2;i<=m;i++) g[i]=(g[i-1]*g[1])/*,pr(g[i])*/;
	for(int i=1,p;i<(1<<n);i++)
	{
		p=lowbit(i);
		for(int j=1;j<(1<<n);j++)
			if((i&j)==j && (p&j) && j!=i)
			{
				f[i]+=(g[0]-f[j])*g[dp[j][i^j]];
//				printf("f[%d]=",i);pr(f[i]);
			}
	}
	poly& rez=f[(1<<n)-1];
	long double ans=0;
//	pr(rez);
	for(int i=0;i<=rez.d;i++) ans+=rez.a[i]/(long double)(i+1);
	printf("%.06lf ",(double)ans);
	return 0;
}
