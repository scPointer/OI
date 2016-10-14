//#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef double db;
const int N=17;
//const ll mod=1e18,shana=10000;
const ll mod=998244353,shana=10000;
int n;
ll g[N][N],a[1<<N],b[1<<N][N],c[1<<N][N],u2,co[233][233];

ll shanquan2(ll a,ll b)
{
	ll ans=1;
	for(;b;b>>=1ll)
	{
		if(b&1ll)ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}

void mokou()
{
	int i,j,k;
	ll ans;
	ans=shanquan2(shana,n*(n-1)/2);
	for(i=0;i<=200;i++)
	{
		co[i][0]=1;
		for(j=1;j<i;j++)
		{
			co[i][j]=(co[i-1][j-1]+co[i-1][j])%mod;
		}
		co[i][i]=1;
	}
	for(i=1;i<n;i++)
	{
		ans=(ans+co[n][i]*shanquan2(shana/2ll,i*(n-i))%mod*shanquan2(shana,n*(n-1)/2-i*(n-i)))%mod;
	}
	printf("%lld\n",ans*shanquan2(shana,n*(n-1)/2)%mod);
}

int main()
{
	int i,j,k,m,u,v;
	ll o,ans;
	scanf("%d%d",&n,&m);
	if(!m)
	{
		mokou();
		return 0;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			g[i][j]=5000;
		}
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&k);
		g[u][v]=k;
		g[v][u]=10000-k;
	}
	/*for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("i=%d j=%d g[i][j]=%lld\n",i,j,g[i][j]);
		}
	}*/
	for(i=0;i<(1<<n);i++)
	{
		a[i]=1;
		for(u=1;u<=n;u++)
		{
			for(v=u+1;v<=n;v++)
			{
				//if(u==v)continue;
				if((i&(1<<(u-1))) && (i&(1<<(v-1))))a[i]=a[i]*shana%mod;
				if((i&(1<<(u-1))) && !(i&(1<<(v-1))))a[i]=a[i]*g[v][u]%mod;
				//if((i&(1<<(u-1))) && !(i&(1<<(v-1))))printf("i=%d u=%d v=%d\n",i,u,v);
				if(!(i&(1<<(u-1))) && (i&(1<<(v-1))))a[i]=a[i]*g[u][v]%mod;
				if(!(i&(1<<(u-1))) && !(i&(1<<(v-1))))a[i]=a[i]*shana%mod;
			}
		}
//		printf("i=%d a[i]=%lld\n",i,a[i]);
	}
	/*u2=shanquan2(shana,mod-2);
	for(i=0;i<(1<<n);i++)
	{
		for(u=1;u<=n;u++)
		{
			b[i][u]=1;
			for(v=1;v<=n;v++)
			{
				if(i&(1<<(v-1)) || u==v)continue;
				b[i][u]=b[i][u]*g[v][u]%mod*u2%mod;
				//if(i==56)printf("i=%d u=%d v=%d b[i][u]=%lld g[v][u]=%lld u2=%lld\n",i,u,v,b[i][u],g[v][u],u2);
			}
			//printf("i=%d u=%d b[i][u]=%lld\n",i,u,b[i][u]);
		}
	}
	for(i=0;i<(1<<n);i++)
	{
		for(u=1;u<=n;u++)
		{
			c[i][u]=1;
			for(v=1;v<=n;v++)
			{
				if(!(i&(1<<(v-1))) || u==v)continue;
				c[i][u]=c[i][u]*g[u][v]%mod*u2%mod;
			}
		}
	}*/
	
	ans=shanquan2(shana,n*(n-1)/2);
	
	//printf("ans=%lld\n",ans);
	/*for(u=1;u<=n;u++)
	{
		for(v=1;v<=n;v++)
		{
			if(u==v)continue;
			for(i=0;i<(1<<n);i++)
			{
				if(i&(1<<(u-1)) || !(i&(1<<(v-1))))continue;
				//printf("u=%d v=%d i=%d\n",u,v,i);
				ans=(ans+a[i]*b[i][u]%mod*c[i][v])%mod;
				if(i==56)printf("u=%d v=%d i=%d a[i]=%lld b[i][u]=%lld c[i][v]=%lld\n",u,v,i,a[i],b[i][u],c[i][v]);
			}
			printf("u=%d v=%d ans=%lld\n",u,v,ans);
		}
	}*/
	for(i=1;i<(1<<n)-1;i++)
	{
		//if(i&(1<<(u-1)) || !(i&(1<<(v-1))))continue;
		//printf("u=%d v=%d i=%d\n",u,v,i);
		//ans=(ans+a[i]*b[i][u]%mod*c[i][v])%mod;
		ans=(ans+a[i])%mod;
		//if(i==56)printf("u=%d v=%d i=%d a[i]=%lld b[i][u]=%lld c[i][v]=%lld\n",u,v,i,a[i],b[i][u],c[i][v]);
	}
	//printf("ans=%lld\n",ans);
	
	printf("%lld\n",ans*shanquan2(shana,n*(n-1)/2)%mod);
	return 0;
}

