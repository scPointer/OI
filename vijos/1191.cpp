#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 105
#define MAXK 11
#define MININT -500000000
int n,m,k;
int dp[MAXN][MAXK][5];
int matrix[MAXN][3];
void solve1()
{
	dp[1][1][1]=matrix[1][1];dp[1][0][0]=0;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			dp[i][j][0]=max(dp[i-1][j][1],dp[i-1][j][0]);
			dp[i][j][1]=max(dp[i][j-1][0]+matrix[i][1],dp[i-1][j][1]+matrix[i][1]);
		}
	printf("%d",max(dp[n][k][1],dp[n][k][0]));
}
void solve2()
{
	for(int i=0;i<=k;i++)
		for(int j=0;j<=4;j++)
			dp[1][i][j]=MININT;
	dp[1][1][1]=matrix[1][1];
	dp[1][1][2]=matrix[1][2];
	dp[1][2][3]=dp[1][1][4]=matrix[1][1]+matrix[1][2];
	for(int i=2;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			dp[i][j][0]=max(max(max(dp[i-1][j][0],dp[i-1][j][1]),max(dp[i-1][j][2],dp[i-1][j][3])),dp[i-1][j][4]);
			dp[i][j][1]=max(max(dp[i][j-1][0]+matrix[i][1],dp[i-1][j][1]+matrix[i][1]),dp[i-1][j][3]+matrix[i][1]);
			dp[i][j][2]=max(max(dp[i][j-1][0]+matrix[i][2],dp[i-1][j][2]+matrix[i][2]),dp[i-1][j][3]+matrix[i][2]);
			dp[i][j][3]=max(dp[i-1][j][3]+matrix[i][1]+matrix[i][2],
							max(dp[i-1][j-1][1]+matrix[i][1]+matrix[i][2],dp[i-1][j-1][2]+matrix[i][1]+matrix[i][2]));
			if(j>=2) dp[i][j][3]=max(dp[i][j][3],dp[i][j-2][0]+matrix[i][1]+matrix[i][2]);
			dp[i][j][4]=max(dp[i-1][j][4]+matrix[i][1]+matrix[i][2],dp[i][j-1][0]+matrix[i][1]+matrix[i][2]);
		}
	printf("%d",max(max(max(dp[n][k][0],dp[n][k][1]),max(dp[n][k][2],dp[n][k][3])),dp[n][k][4]));
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&matrix[i][j]);
	if(m==1)
		solve1();
	else solve2();
	return 0;
}
