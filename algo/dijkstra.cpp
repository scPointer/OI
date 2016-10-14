#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
//#define N 50005
//#define M 50005
#define INF 100000000000000ll
#define mp make_pair
#define fst first
#define scd second
#define failed(x) {std::cout<<x;return 0;}
#define dbg(x) {std::cout<<#x<<' '<<x<<std::endl;}
typedef long long ll;
namespace Dijkstra
{
#define PLI pair<long long,int>
struct Edge{
	int pfr,pto;
	ll len;
}eg[M];
int nxt[M],head[N],egtot;
ll dis[N];
bool vis[N];
int n,m,s,t;
void init(int _n,int _m,int _s,int _t)
{
	n=_n;m=_m;s=_s;t=_t;
	for(int i=0;i<=n;i++)
		head[i]=-1;
}
void addEdge(int p1,int p2,ll len)
{
	eg[egtot]=(Edge){p1,p2,len};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}
void dijkstra()
{
	priority_queue<PLI,vector<PLI >,greater<PLI > > pq;
	for(int i=0;i<=n;i++)
		vis[i]=0,dis[i]=INF;
	dis[s]=0;
	pq.push(mp(dis[s],s));
	while(!pq.empty())
	{
		pair<ll,int> p;
		do{
			p=pq.top();pq.pop();
		}while(!pq.empty() && vis[p.scd]);
		if(vis[p.scd]) break;
		vis[p.scd]=1;
		for(int i=head[p.scd];~i;i=nxt[i])
			if(dis[eg[i].pto]>dis[p.scd]+eg[i].len)
			{
				dis[eg[i].pto]=dis[p.scd]+eg[i].len;
				pq.push(mp(dis[eg[i].pto],eg[i].pto));
			}
	}
}

}