#include <cstdio>
#include <iostream>
inline int RD()
{
	int res=0,sign=1;
	char cr;
	while( (cr=getchar())<'0' || cr>'9')
		if(cr=='-') break;
	if(cr=='-') sign=-1;
	else res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<3)+(res<<1)+cr-'0';
	return res;
}
#define N 1000005
#define dbg(x) printf("%s=%d\n",#x,x)
typedef long long ll;
ll dis[N],sum[N],a[N],cost[N],dp[N];
int main()
{
	freopen("1096.in","r",stdin);
	int n=RD();
	for(int i=1;i<=n;i++)
	{
		dis[i]=RD();
		sum[i]=sum[i-1]+RD();
		a[i]=RD();
	}
	for(int i=2;i<=n;i++)
		cost[i]=cost[i-1]+sum[i-1]*(dis[i]-dis[i-1]);
//	int pos;
	ll res;
	for(int i=1;i<=n;i++)
	{
		dp[i]=1ll<<62;
		int mx=0;
		for(int pos=0;pos<i;pos++)
		{
			res=dp[pos]+cost[i]-cost[pos]-sum[pos]*(dis[i]-dis[pos])+a[i];
			if(res<=dp[i]) dp[i]=res,mx=pos;
		}
		if(i<=60) dbg(i),dbg(mx);
	}
	std::cout<<dp[n];
}