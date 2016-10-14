//0/1-indexed Node
//0-indexed Edge
#define M
#define NDS
namespace MF
{
 
struct Edge{int pfr,pto,flo,lim;}eg[M];
int head[NDS],nxt[M],egtot;
int S,T,nds;
void addEdge(int p1,int p2,int lim)
{
//  dbg(p1);dbg(p2);dbg(cst);
    eg[egtot]=(Edge){p1,p2,0,lim};
    nxt[egtot]=head[p1];
    head[p1]=egtot++;
    eg[egtot]=(Edge){p2,p1,0,0};
    nxt[egtot]=head[p2];
    head[p2]=egtot++;
}
void init(int _s,int _t,int _nds)
{
	egtot=0;
    S=_s;
    T=_t;
    nds=_nds;
    for(int i=0;i<=nds;i++)
        head[i]=-1;
}
int hd[NDS];
int stg[NDS];
int q[NDS];
bool markstage()
{
	for(int i=0;i<=nds;i++)
		stg[i]=-1;
	stg[S]=0;
	int l,r,p;
	q[l=r=1]=S;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];~i;i=nxt[i])
		{
			Edge& e=eg[i];
			if(e.flo<e.lim && stg[e.pto]==-1)
			{
				stg[e.pto]=stg[p]+1;
				q[++r]=e.pto;
			}
		}
	}
	return stg[T]!=-1;
}
ll dfs(int p,ll a)
{
	if(p==T || a==0) return a;
	ll flow=0,f;
	for(;~hd[p];hd[p]=nxt[hd[p]])
	{
		Edge& e=eg[hd[p]];
		if(stg[e.pto]==stg[p]+1 && (f=dfs(e.pto,Min(e.lim-e.flo,a)))>0)
		{
			flow+=f;
			a-=f;
			e.flo+=f;
			eg[hd[p]^1].flo-=f;
			if(a==0) break;
		}
	}
	return flow;
}
void solve(ll& flow)
{
	flow=0;
	while(markstage())
	{
		for(int i=0;i<=nds;i++) hd[i]=head[i];
		flow+=dfs(S,INF);
	}
}
void solve(int& flow)
{
    ll _flow=0;
    solve(_flow);
    flow=_flow;
}
 
};