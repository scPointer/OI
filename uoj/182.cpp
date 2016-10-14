#include <cstdio>
#define N 100050
#define MO 998244353
long long commd[N][2];
long long v[N];
int n,m;
inline void Read(int& res)
{
	static char cr;
	while((cr=getchar())<'0' ||cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
}
inline void Read(long long& res)
{
	static char cr;
	while((cr=getchar())<'0' ||cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
}
void solve2()
{
	long long ans=0;
	for(int i=1;i<=m;i++)
		ans=(ans+commd[i][1]*n)%MO;
	for(int i=1;i<=n;i++)
		ans=(ans+v[i])%MO;
	printf("%lld\n",ans);
}
void gcd(long long a,long long b,long long& d,long long& x,long long& y)
{
	if(!b){d=a;x=1;y=0;}
	else{gcd(b,a%b,d,y,x);y-=a/b*x;}
}
void solve1()
{
	for(int i=1;i<=m;i++)
	{
		if(commd[i][0]==1)
		{
			for(int j=1;j<=n;j++)
				v[j]=(v[j]+commd[i][1])%MO;
		}
		else
		{
			long long x,y,d;
			for(int j=1;j<=n;j++)
			{
				gcd(v[j],MO,d,x,y);
				v[j]=(x+MO)%MO;
			}
		}
		long long ans=0;
		for(int j=1;j<=n;j++)
			ans=(ans+v[j])%MO;
		printf("%lld\n",ans);
	}
}
int main()
{
	bool ifpoint2=1;
	Read(n);Read(m);
	for(int i=1;i<=n;i++) Read(v[i]);
	for(int i=1;i<=m;i++)
	{
		Read(commd[i][0]);
		if(commd[i][0]==1) Read(commd[i][1]);
		else ifpoint2=0;
	}
	if(ifpoint2) solve2();
	else solve1();
	return 0;
}
