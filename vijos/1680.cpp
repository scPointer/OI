#include <cstdio>
#include <cstring>
#define MAXN 2005
#define MIN(a,b) (a<b?a:b)
char a[MAXN],b[MAXN];
int dp[MAXN][MAXN];
inline int dist(char c1,char c2){return c1>c2?c1-c2:c2-c1;}
int main()
{
	int k;
	scanf("%s",a);
	scanf("%s",b);
	scanf("%d",&k);
	int alen=strlen(a);
	int blen=strlen(b);
	for(int i=0;i<=alen;i++)
		dp[i][0]=i*k;
	for(int j=0;j<=blen;j++)
		dp[0][j]=j*k;
	for(int i=1;i<=alen;i++)
		for(int j=1;j<=blen;j++)
			dp[i][j]=MIN(dp[i-1][j-1]+dist(a[i-1],b[j-1]),MIN(dp[i-1][j]+k,dp[i][j-1]+k));
	printf("%d",dp[alen][blen]);
	return 0;
}
