#include <cstdio>
#include <algorithm>
#define MAXN 10005
#define MAXM 1005
#define INF 20000000
#define min(a,b) (a<b?a:b)
int n,m,k;
int x[MAXN],y[MAXN];
int dp[MAXN][MAXM];
int downdp[MAXN][MAXM];
struct PIPE{
	int p;
	int l;
	int h;
}pi[MAXN];
int toppi;
bool cmp(PIPE a,PIPE b){return a.p<b.p;}
int main()
{
//	freopen("bird.in","r",stdin);
//	freopen("bird.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<=n-1;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=0;i<=k-1;i++)
		scanf("%d%d%d",&pi[i].p,&pi[i].l,&pi[i].h);
	std::sort(pi,pi+k,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
			downdp[i][j]=dp[i][j]=INF;
//		undown[i][m]=1;
	}
//	int x=0;
	for(int i=0;i<=n-1;i++)
	{
//		x=1-x;
//		for(int j=0;j<=m;j++)
//			dp[j][x]=INF;
		int  d=1,u=m;
		if(toppi<=k-1&&pi[toppi].p==i)
		{
			d=pi[toppi].l+1,u=pi[toppi].h-1;
			toppi++;
		}
		
		for(int j=d;j<=u;j++)
		{
			if(j>y[i]) downdp[i+1][j-y[i]]=dp[i][j];
			if(j+x[i]<m) dp[i+1][j+x[i]]=min(dp[i][j]+1,dp[i+1][j+x[i]]);
			else dp[i+1][m]=min(dp[i][j]+1,dp[i+1][m]);
		}
		for(int j=x[i]+1;j<=m;j++)
			dp[i+1][j]=min(dp[i+1][j-x[i]]+1,dp[i+1][j]);
		for(int j=m+1;j<m+x[i];j++)
			dp[i+1][m]=min(dp[i+1][j-x[i]]+1,dp[i+1][m]);
		for(int j=1;j<=m;j++)
			dp[i+1][j]=min(dp[i+1][j],downdp[i+1][j]);
		
		bool flag=0;
		for(int j=1;j<=m;j++)
			if(dp[i+1][j]<INF) {flag=1;break;}
		if(flag==0)
		{
			printf("0\n%d",toppi-1);
			return 0;
		}
	}
	int mintimes=INF;
	for(int j=1;j<=m;j++)
		if(dp[n][j]<mintimes) mintimes=dp[n][j];
	printf("1\n%d",mintimes);
	return 0;
}
