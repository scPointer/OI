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
typedef long long ll;
ll dis[N],sum[N],a[N],cost[N],dp[N];
int q[N];
double getk(int a,int b)
{
	return (cost[b]-cost[a]+sum[a]*dis[a]-sum[b]*dis[b]+dp[a]-dp[b])/(double)(sum[a]-sum[b]);
}
ll calc(int i,int pos)
{
	return dp[pos]+cost[i]-cost[pos]-sum[pos]*(dis[i]-dis[pos])+a[i];
}
int main()
{
	int n=RD();
	for(int i=1;i<=n;i++)
	{
		dis[i]=RD();
		sum[i]=sum[i-1]+RD();
		a[i]=RD();
	}
	for(int i=2;i<=n;i++)
		cost[i]=cost[i-1]+sum[i-1]*(dis[i]-dis[i-1]);
	int l=1,r=2;
	q[1]=0,q[2]=1;
	dp[1]=a[1];
	ll res;
	for(int i=2;i<=n;i++)
	{
		while(l<r && dis[i]>getk(q[l],q[l+1])) l++;
		dp[i]=calc(i,q[l]);
		while(l<r && getk(q[r-1],q[r])>getk(q[r],i)) r--;
		q[++r]=i;
	}
	std::cout<<dp[n];
}