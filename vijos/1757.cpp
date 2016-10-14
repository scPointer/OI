#include <cstdio>
#define N 1005
#define K 1005
#define MO 10000
int dp[N][K];
int main()
{
	int T,n,k,i=1;
	dp[0][0]=1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		for(;i<=n;i++)
		{
			dp[i][0]=1;
			for(int j=1;j<i && j<K;j++)
				dp[i][j]=(dp[i][j-1]+dp[i-1][j])%MO;
			for(int j=i;j<K;j++)
				dp[i][j]=(dp[i][j-1]+dp[i-1][j]-dp[i-1][j-i]+MO)%MO;	
		}
		printf("%d\n",dp[n][k]);
	}
}