#include <cstdio>
#include <cstring>
#define N 55
#define mo 10000007
typedef long long ll;
ll n;
ll f[N][N];
int div(ll n)
{
	int res=-1;
	while(n) res++,n>>=1;
	return res;
}
ll fastpow(ll  d,ll p)
{
	ll res=1;
	while(p)
	{
		if(p&1) res=(res*d)%mo;
		d=(d*d)%mo;
		p>>=1;
	}
	return res;
}
ll dfs(int bt,int num,bool top)
{
	if(bt==-1) return num==0;
	if(!top && f[bt][num]!=-1) return f[bt][num];
	ll res=0;
	if(bt>=num) res=dfs(bt-1,num,top&&((n&(1ll<<bt))==0));
	if(num>0 && (!top || (n&(1ll<<bt)))) res=(res+dfs(bt-1,num-1,top));
	if(!top) f[bt][num]=res;
	return res;
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%lld",&n);
	int bits=div(n);
	ll ans=1;
	for(int i=2;i<=bits+1;i++)
		ans=(ans*fastpow(i,dfs(bits,i,1)))%mo;
	printf("%lld",ans);
}