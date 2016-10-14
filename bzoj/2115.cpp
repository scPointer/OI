#include <cstdio>
#include <algorithm>
#define Swap(a,b) std::swap(a,b)
#define Max(a,b) (a>b?a:b)
#define N 50005
#define M 200005
typedef long long ll;
inline ll RD()
{
	static ll res;
	static char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
int eg[M*2],nxt[M*2],head[N],egtot;
ll wi[M*2];
ll dis[N];
bool vis[N];
ll rud[M*2],rcnt,ccnt;
void addEdge(int p1,int p2,ll w)
{
	eg[++egtot]=p2;
	wi[egtot]=w;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
void dfs(int p)
{
	for(int i=head[p];i;i=nxt[i])
		if(vis[eg[i]]==0)
		{
			vis[eg[i]]=1;
			dis[eg[i]]=dis[p]^wi[i];
			dfs(eg[i]);
		}
		else
			rud[++rcnt]=wi[i]^dis[p]^dis[eg[i]];
}
void setBase()
{
	for(int i=63;i>=0;i--)
	{
		int pt=-1;
		for(int j=ccnt+1;j<=rcnt;j++)
			if((rud[j]&(1ll<<i)))
			{pt=j;break;}
		if(pt==-1) continue;
		++ccnt;
		Swap(rud[pt],rud[ccnt]);
		for(int j=ccnt+1;j<=rcnt;j++)
			if(rud[j]&(1ll<<i))
				rud[j]^=rud[ccnt];
	}
}
int main()
{
	int n,m; n=RD();m=RD();
	ll w;
	for(int i=1,p1,p2;i<=m;i++)
	{
		p1=RD();p2=RD();w=RD();
		addEdge(p1,p2,w);
		addEdge(p2,p1,w);
	}
	vis[1]=1;dfs(1);
	setBase();
	ll ans=dis[n];
	for(int i=1;i<=ccnt;i++)//WA: for(int i=ccnt;i>=1;i--)
		ans=Max(ans,(ans^rud[i]));
	printf("%lld\n",ans);
}