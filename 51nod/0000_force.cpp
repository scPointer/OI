#include <cstdio>
#include <algorithm>
#define N 7//53
inline int RD()
{
	int res;char cr;
	while( (cr=getchar())<'0' || cr>'9'); res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9') res=res*10+cr-'0';
	return res;
}
struct Temp{int p,w;}tp[N][N];
int n,m;
int cnt[N];
int stk[N],res[N];
double ans;
void dfs(int x,double p)
{
	if(x>n)
	{
		for(int i=1;i<=n;i++) res[i]=stk[i];
		std::sort(res+1,res+1+n);
		double sumw=0;
		for(int i=n;i>=n-m+1;i--)
			sumw+=res[i];
		ans+=p*sumw;
		return;
	}
	for(int i=1;i<=cnt[x];i++)
	{
		stk[x]=tp[x][i].w;
		dfs(x+1,p*tp[x][i].p/10000.0);
	}
}
int main()
{
	freopen("p0000.in","r",stdin);
	n=RD();m=RD();
	for(int i=1;i<=n;i++)
	{
		cnt[i]=RD();
		for(int j=1;j<=cnt[i];j++)
		{
			tp[i][j].w=RD();
			tp[i][j].p=RD();
		}
	}
	dfs(1,1);
	printf("%.9lf",ans);
}