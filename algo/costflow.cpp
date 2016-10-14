//1-indexed Node
//0-indexed Edge
#include <cstdio>
#include <cstring>
#define N 100050
#define M 500050
#define QUELIM M<<2
#define INF 100000000000000ll
#define Min(a,b) (a<b?a:b)
typedef long long ll;
namespace costflow
{

struct Edge{int pfr,pto,flo,lim,cst;}eg[M];
int head[N],nxt[M],egtot;
int S,T,nds;
void addEdge(int p1,int p2,int lim,int cst)
{
	eg[egtot]=(Edge){p1,p2,0,lim,cst};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot]=(Edge){p2,p1,0,0,-cst};
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
void init(int n,int m,int _s,int _t,int _nds)
{
	S=_s;
	T=_t;
	nds=_nds;
	for(int i=1;i<=n;i++)
		head[i]=-1;
}
ll dis[N];
int pre[N],q[QUELIM];
bool inq[N];
void solve(ll& flow,ll& cost)
{
	flow=cost=0;
	while(1)
	{
		for(int i=1;i<=nds;i++)
			dis[i]=INF,pre[i]=-1,inq[i]=0;
		dis[S]=0;
		int l=0,r=1,p;
		q[l]=S;
		while(l<r)
		{
			p=q[l++];inq[p]=0;
//			if(l==QUELIM) l=0; 
			for(int i=head[p];~i;i=nxt[i])
			{
				Edge& e=eg[i];
				if(e.flo<e.lim && dis[e.pto]>dis[p]+e.cst)
				{
					dis[e.pto]=dis[p]+e.cst;
					pre[e.pto]=i;
					if(!inq[e.pto])
					{
						inq[e.pto]=1;
						q[r++]=e.pto;
//						if(r==QUELIM) r=0;
					}
				}
			}
		}
		if(dis[T]==INF) break;
		ll f=INF;
		for(int p=pre[T];~p;p=pre[eg[p].pfr])
			f=Min(f,eg[p].lim-eg[p].flo);
		for(int p=pre[T];~p;p=pre[eg[p].pfr])
		{
			eg[p].flo+=f;
			eg[p^1].flo-=f;
		}
		flow+=f;
		cost+=f*dis[T];
	}
}

void solve(int& flow,int& cost)
{
	ll _flow=0,_cost=0;
	solve(_flow,_cost);
	flow=_flow;cost=_cost;
}

};
