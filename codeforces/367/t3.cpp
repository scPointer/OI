#include <cstdio>
#define N 100005
#define INF 10000000000000000ll
#define Min(a,b) (a<b?a:b)
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int n;
int cost[N];
char s[N*3];
int fst[N],len[N],tail;
int avail[N];
long long dp[N][2];
inline void readStr(int p)
{
	char cr;
	while( (cr=getchar())<'a' || cr>'z');
	fst[p]=tail;
	s[tail++]=cr;
	while( (cr=getchar())>='a' && cr<='z')
		s[tail++]=cr;
	len[p]=tail-fst[p];
}
bool cmp(int a,int b,int ca,int cb)
{
	int p1= ca? fst[a]+len[a]-1: fst[a];
	int p2= cb? fst[b]+len[b]-1: fst[b];
	while(1)
	{
		if(s[p1]<s[p2]) return 1;
		else if(s[p1]>s[p2]) return 0;
		ca? --p1:++p1;
		cb? --p2:++p2;
		if(p1<fst[a] || p1>=fst[a]+len[a])
			return 1;
		else if(p2<fst[b] || p2>=fst[b]+len[b])
			return 0;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&cost[i]);
	for(int i=1;i<=n;i++)
		readStr(i);
	dp[1][0]=0;dp[1][1]=cost[1];
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=dp[i][1]=INF;
		if(cmp(i-1,i,0,0))
			dp[i][0]=Min(dp[i][0],dp[i-1][0]);
		if(cmp(i-1,i,0,1))
			dp[i][1]=Min(dp[i][1],dp[i-1][0]+cost[i]);
		if(cmp(i-1,i,1,0))
			dp[i][0]=Min(dp[i][0],dp[i-1][1]);
		if(cmp(i-1,i,1,1))
			dp[i][1]=Min(dp[i][1],dp[i-1][1]+cost[i]);
	}
	long long ans=Min(dp[n][0],dp[n][1]);
	if(ans==INF) printf("-1");
	else printf("%I64d",ans);
}
