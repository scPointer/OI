#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define N 505
#define M 50005
#define QUELIM 50005
#define INF 100000000000000ll
#define mp make_pair
#define fst first
#define scd second
#define failed(x) {std::cout<<x;return 0;}
#define dbg(x) {std::cout<<#x<<'='<<x<<std::endl;}
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define ls (p<<1)
#define rs ((p<<1)|1)
typedef long long ll;
namespace costflow
{

struct Edge{int pfr,pto,flo,lim,cst;}eg[M];
int head[N],nxt[M],egtot;
int S,T,nds;
void addEdge(int p1,int p2,int lim,int cst)
{
//	dbg(p1);dbg(p2);dbg(cst);
	eg[egtot]=(Edge){p1,p2,0,lim,cst};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot]=(Edge){p2,p1,0,0,-cst};
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
void init(int _s,int _t,int _nds)
{
	S=_s;
	T=_t;
	nds=_nds;
	for(int i=0;i<=nds;i++)
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
using namespace costflow;
int gc()
{
	char cr;
	while( (cr=getchar())<'A' || cr>'Z');
	if(cr=='U') return 0;
	else if(cr=='R') return 1;
	else if(cr=='D') return 2;
	else return 3;
}
int dir[255][4];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	init(n*m*2+1,n*m*2+2,n*m*2+2);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int p=(i-1)*m+j;
			dir[p][0]= i>1? p-m:p-m+n*m;
			dir[p][2]= i<n? p+m:p+m-n*m;
			dir[p][3]= j>1? p-1:p-1+m;
			dir[p][1]= j<m? p+1:p+1-m;
			for(int k=0;k<4;k++)
				dir[p][k]+=n*m;
			addEdge(S,p,1,0);
			addEdge(p+n*m,T,1,0);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int cr=gc();
			int p=(i-1)*m+j;
			for(int k=0;k<=3;k++)
			{
				if(k==cr)
					addEdge(p,dir[p][k],1,0);
				else
					addEdge(p,dir[p][k],1,1);
			}
		}
	int flow,cost;
	solve(flow,cost);
	printf("%d",cost);
}
