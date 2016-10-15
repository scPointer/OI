#include <cstdio>
#include <iostream>
typedef long long ll;
#define INF 10000000000000000ll
#define Min(a,b) (a<b?a:b)
ll dp[105][105][105];
ll pre[105][105][105];
ll flo[105][105][105];
ll cost[105][105];
ll clr[105];
int main()
{
	int n,m,cnt;scanf("%d%d%d",&n,&m,&cnt);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);clr[i]=p;
	}
	for(int i=1,p;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&p);cost[i][j]=p;
		}
	ll setans=0;
	for(int i=1;i<=n;i++)
		if(clr[i]!=0)
			setans-=cost[i][clr[i]];
	for(int i=0;i<=n;i++)
	for(int j=0;j<=m+1;j++)
		for(int k=0;k<=cnt+1;k++)
			pre[i][j][k]=flo[i][j][k]=dp[i][j][k]=INF;
	for(int j=1;j<=m;j++)
		dp[0][j][1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			for(int k=1;k<=cnt;k++)
			{
				dp[i][j][k]=Min(Min(dp[i-1][j][k],pre[i-1][j-1][k-1]),flo[i-1][j+1][k-1])+cost[i][j];
			}
		if(clr[i]!=0)
		{
			for(int j=1;j<=m;j++)
			{
				if(j==clr[i]) continue;
				for(int k=1;k<=cnt;k++)
					dp[i][j][k]=INF;
			}
		}
		for(int k=1;k<=cnt;k++)
		{
			pre[i][0][k]=INF;
			flo[i][m+1][k]=INF;
			for(int j=1;j<=m;j++)
				pre[i][j][k]=Min(dp[i][j][k],pre[i][j-1][k]);
			for(int j=m;j>=1;j--)
				flo[i][j][k]=Min(dp[i][j][k],flo[i][j+1][k]);
		}
	}
	ll ans=pre[n][m][cnt];
	if(ans<INF) std::cout<<ans+setans;
	else std::cout<<"-1";
}