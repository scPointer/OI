#include <cstdio>
#include <queue>
using namespace std;
#define N 405
#define M 80005
#define INF 500000000000000000ll
#define Min(a,b) (a<b?a:b)
struct Edge{int pfr,pto,flo,lim,cst;}eg[M];
int head[N],nxt[M],egtot;
void initEdge(int nds){for(int i=1;i<=nds;i++) head[i]=-1;}
void addEdge(int p1,int p2,int lim,int cst)
{
	eg[egtot]=(Edge){p1,p2,0,lim,cst};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot]=(Edge){p2,p1,0,0,-cst};
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
long long dis[N];
int pre[N];
bool inq[N];
queue<int> q;
void maxflow(int S,int T,int nds)
{
	long long flow=0,cost=0;
	while(1)
	{
		for(int i=1;i<=nds;i++) dis[i]=INF,inq[i]=0;
		dis[S]=0;pre[S]=-1;
		q.push(S);inq[S]=1;
		int p;
		while(!q.empty())
		{
			p=q.front();q.pop();inq[p]=0;
			for(int i=head[p];i!=-1;i=nxt[i])
			{
				Edge& e=eg[i];
				if(e.flo<e.lim && dis[e.pto]>dis[p]+e.cst)
				{
					dis[e.pto]=dis[p]+e.cst;
					pre[e.pto]=i;
					if(inq[e.pto]==0)
						inq[e.pto]=1,q.push(e.pto);
				}
			}
		}
		if(dis[T]==INF) break;
		int f=1<<30;
		for(int i=pre[T];i!=-1;i=pre[eg[i].pfr])
			f=Min(f,eg[i].lim-eg[i].flo);
		flow+=f;
		for(int i=pre[T];i!=-1;i=pre[eg[i].pfr])
		{
			f=eg[i].lim-eg[i].flo;
			cost+=eg[i].cst;
			eg[i].flo+=f;
			eg[i^1].flo-=f;
		}
	}
	printf("%lld %lld",flow,cost);
}
int main()
{
	int n,m,S,T,nds;
	scanf("%d%d",&n,&m);
	S=n+1,T=n;nds=n*2;
	initEdge(n*2);
	for(int i=1,p1,p2,cst;i<=m;i++)
	{
		scanf("%d%d%d",&p1,&p2,&cst);
		addEdge(p1+n,p2,1,cst);
	}
	for(int i=2;i<=n-1;i++)
		addEdge(i,i+n,1,0);
	maxflow(S,T,nds);
}