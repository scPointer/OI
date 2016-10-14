#include <cstdio>
#define L 75005
#define N 255
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
long long dp[L][4];
inline int RD()
{
	static char cr;
	static int res;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int n,k,ll,rr;
int sum[N];
int w[N];
int reach[L],cnt;
long long maxbit=(long long)(1<<30)*(1<<30)*8;
void getdp()
{
	int top=k>>6;
	int l;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=sum[i];j>=w[i];j--)
		{
			dp[j][0]|=dp[j-w[i]][0]<<1;
			for(l=1;l<=top;l++)
				dp[j][l]|=(dp[j-w[i]][l-1] & maxbit)&&1,
				dp[j][l]|=dp[j-w[i]][l]<<1;
		}
	l=(k-64*top);
	for(int i=0;i<=sum[n];i++)
		if(dp[i][top]&(1<<l))
			reach[++cnt]=i;
}
int main()
{
	n=RD();k=RD();ll=RD();rr=RD();
	for(int i=1;i<=n;i++) sum[i]= (w[i]=RD())+sum[i-1];
	getdp();reach[0]=-1000000;reach[++cnt]=1000000;
	int ans=0,p=1;
	for(int i=ll;i<=rr;i++)
	{
		while(p<cnt && reach[p]<i) p++;
		ans=Max(ans,Min(reach[p]-i,i-reach[p-1]));
	}
	printf("%d",ans);
}
