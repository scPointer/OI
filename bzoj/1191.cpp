#include <cstdio>
#define N 4005
#define M 20005
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define INF 100000005
int pa[N],pb[N];
int n,m,S,T,nds;
struct Edge{int pfr,pto,flo,lim;}eg[M];
int nxt[M],head[N],egtot;
int hd[N];
int stg[N],q[N];
void addEdge(int pfr,int pto)
{
	eg[egtot]=(Edge){pfr,pto,0,1};
	nxt[egtot]=head[pfr];
	head[pfr]=egtot++;
	eg[egtot]=(Edge){pto,pfr,0,0};
	nxt[egtot]=head[pto];
	head[pto]=egtot++;
}
bool markstage()
{
	
	for(int i=1;i<=nds;i++)
		stg[i]=-1;
	int l,r,p;
	q[l=r=1]=S;stg[S]=0;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];~i;i=nxt[i])
		{
			Edge& e=eg[i];
			if(stg[e.pto]==-1 && e.flo<e.lim)
			{
				stg[e.pto]=stg[p]+1;
				q[++r]=e.pto;
			}
		}
	}
	return ~stg[T];
}
int dfs(int p,int a)
{
	if(p==T || a<=0) return a;
	int flow=0,f;
	for(;~hd[p];hd[p]=nxt[hd[p]])
	{
		Edge& e=eg[hd[p]];
		if(stg[e.pto]==stg[p]+1 && (f=dfs(e.pto,Min(a,e.lim-e.flo)))>0)
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
int Dinic()
{
	int flow=0;
	while(markstage())
	{
		for(int i=1;i<=nds;i++)
			hd[i]=head[i];
		flow+=dfs(S,INF);
	}
	return flow;
}
bool check(int lim)
{
	if(lim==0) return 1;
	for(int i=1;i<=nds;i++)
		head[i]=-1;
	egtot=0;
	for(int i=1;i<=n;i++)
		addEdge(S,i);
	for(int i=n+1;i<=n+lim;i++)
		addEdge(i,T);
	for(int i=1;i<=lim;i++)
		addEdge(pa[i],n+i),addEdge(pb[i],n+i);
	int ans=Dinic();
	return ans==lim;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=n+m+1;T=nds=S+1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&pa[i],&pb[i]);
		++pa[i],++pb[i];
	}
	int l=0,r=m+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%d",l);
}