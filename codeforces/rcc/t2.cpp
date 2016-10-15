#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define N 50005
#define M 200005
#define NDS 200005
#define QUELIM M<<1
#define pb push_back
#define INF 10000000000000000ll
#define Min(a,b) (a<b?a:b)
#define dbg(x) {std::cout<<#x<<'='<<x<<std::endl;}
typedef long long ll;
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
		for(int i=1;i<=nds;i++) hd[i]=head[i];
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

int eg[N<<1],nxt[N<<1],col[N<<1],head[N],egtot;
int used[N<<1];
void addEdge(int p1,int p2,int color)
{
	eg[++egtot]=p2;
	col[egtot]=color;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
int fa[N],pre[N],vis[N];
vector<int> rnd[N];
int rcnt;
int colegs[NDS];
int colcnt[NDS];
int sumcol;
void dfs(int p)
{
	for(int i=head[p],pt;i;i=nxt[i])
		if(eg[i]!=fa[p])
		{
			pt=eg[i];
			if(used[i]) continue;
			else if(vis[pt]==1)
			{
				rcnt++;
				rnd[rcnt].pb(col[i]);
				colcnt[col[i]]--;
				for(int j=p;j!=pt;j=fa[j])
				{
					rnd[rcnt].pb(col[pre[j]]);
					colcnt[col[pre[j]]]--;
					used[pre[j]]=1;
					pre[j]&1? used[pre[j]+1]=1:used[pre[j]-1]=1;
				}
				used[i]=1;
				i&1? used[i+1]=1:used[i-1]=1;
				continue;
			}
			else
			{
				fa[pt]=p;
				pre[pt]=i;
				vis[pt]=1;
				dfs(pt);
			}
		}
}
int hs[N],hcnt;
void initHash()
{
	std::sort(hs+1,hs+1+hcnt);
	int p=1;
	for(int i=2;i<=hcnt;i++)
		if(hs[i]!=hs[i-1])
			hs[++p]=hs[i];
	hcnt=p;
}
int getHash(int p)
{
	int l=1,r=hcnt+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(hs[mid]<=p) l=mid;
		else r=mid;
	}
	return l;
}
int main()
{
//	freopen("t2.in","r",stdin);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,p1,p2,c;i<=m;i++)
	{
		scanf("%d%d%d",&p1,&p2,&c);
		addEdge(p1,p2,c);
		addEdge(p2,p1,c);
		hs[++hcnt]=c;
//		if(colcnt[c]==0) sumcol++;
//		colcnt[c]++;
	}
	initHash();
	for(int i=1;i<=egtot;i+=2)
		col[i]=col[i+1]=getHash(col[i]);
	for(int i=1;i<=egtot;i+=2)
	{
		if(colcnt[col[i]]==0) sumcol++;
		colcnt[col[i]]++;
	}
	m=hcnt;
	vis[1]=1;
	dfs(1);
	MF::init(rcnt+m+1,rcnt+m+2,rcnt+m+2);
	int realround=rcnt;
	for(int i=1;i<=rcnt;i++)
	{
		
		bool flag=0;
		for(int j=rnd[i].size()-1;j>=0;j--)
			if(colcnt[rnd[i][j]]==0)
			{
				MF::addEdge(i,rcnt+rnd[i][j],1);
				colegs[rnd[i][j]]++;
			}
			else flag=1;
		if(flag==0) MF::addEdge(MF::S,i,1);
		else realround--;
	}
	for(int i=1;i<=m;i++)
		if(colegs[i]>0)
		{
			MF::addEdge(rcnt+i,MF::T,colegs[i]-1);
		}
	int flow;
	MF::solve(flow);
	printf("%d",sumcol-realround+flow);
}
