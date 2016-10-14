#include <cstdio>
#define N 200005
#define INF 10000000000000000ll
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
typedef long long ll;
ll eg[N<<1],nxt[N<<1],head[N],len[N<<1],egtot;
ll n,m;
void addEdge(ll p1,ll p2,ll d)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	len[egtot]=d;
	head[p1]=egtot;
}
ll q[N];
ll pre[N];
ll dis1[N],dis2[N];
ll findfurthest(ll& S,ll dis[])
{
	for(ll i=1;i<=n;i++) dis[i]=INF;
	ll l,r,p;
	ll res=S;
	pre[S]=-1;
	q[l=r=1]=S;dis[S]=0;
	while(l<=r)
	{
		p=q[l++];
		for(ll e=head[p];e;e=nxt[e])
			if(dis[eg[e]]==INF)
			{
				dis[eg[e]]=dis[p]+len[e];
				if(dis[eg[e]]>dis[res])
					res=eg[e];
				q[++r]=eg[e];
				pre[eg[e]]=p;
			}
	}
	S=res;
	return dis[res];
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1,p1,p2,d;i<=m;i++)
	{
		scanf("%lld%lld%lld",&p1,&p2,&d);
		addEdge(p1,p2,d);
		addEdge(p2,p1,d);
	}
	ll poi=1;
	findfurthest(poi,dis1);
	ll dist=findfurthest(poi,dis1);
	findfurthest(poi,dis2);
	ll pl=0;
	for(ll p=1;p<=n;p++)
		pl=Max(pl,Min(dis1[p],dis2[p]));
	printf("%lld",dist+pl);
}