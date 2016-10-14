#include <cstdio>
#include <algorithm>
#define N 3005
#define mabs(x) ((x)>0?(x):-(x))
#define Min(a,b) (a<b?a:b)
#define INF 10000000000000000ll
typedef long long ll;
int a[N];
int b[N],bcnt;
ll dp[2][N];
int n;
void init()
{
	bcnt=1;
	for(int i=2;i<=n;i++)
		if(b[i]!=b[i-1])
			b[++bcnt]=b[i];
}
int main()
{
	scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		b[i]=a[i]=p-i;
	}
	std::sort(b+1,b+n+1);
	init();
	int x=0;
	for(int i=1;i<=n;i++)
	{
		x^=1;
		for(int j=1;j<=bcnt;j++)
			dp[x][j]=INF;
		ll mn=INF;
		for(int j=1;j<=bcnt;j++)
		{
			mn=Min(mn,dp[x^1][j]);
			dp[x][j]=Min(dp[x][j],mn+mabs(b[j]-a[i]));
		}
	}
	ll ans=INF;
	for(int j=1;j<=bcnt;j++)
		ans=Min(ans,dp[x][j]);
	printf("%I64d",ans);
}
