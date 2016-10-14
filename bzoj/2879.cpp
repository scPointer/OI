#include <cstdio>
#include <cstring>
#define N 100005
#define M 2000005
#define INF (1ll<<60)
struct Edge{int pfr,pto,flo,cst;}eg[M];
int head[N],nxt[M],egtot;
int S,T,nds;
void addEdge(int p1,int p2,int flo,int cst)
{
	eg[egtot]=(Edge){p1,p2,flo,cst};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot]=(Edge){p2,p1,0,-cst};
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
int q[M*5],pre[N];
long long dis[N];
bool inq[N];
int mtx[42][102];
int peo[N],sp;
long long maxflow(int n,int m)
{
	long long cost=0;
	while(1)
	{
		for(int i=1;i<=nds;i++) pre[i]=inq[i]=0,dis[i]=INF;
		int l,r,p; q[l=r=1]=S;
		dis[S]=0;pre[S]=-1;inq[S]=1;
		while(l<=r)
		{
			p=q[l++];inq[p]=0;
			for(int i=head[p];~i;i=nxt[i])
			{
				Edge& e=eg[i];
				if(e.flo && dis[e.pto]>dis[p]+e.cst)
				{
					dis[e.pto]=dis[p]+e.cst;
					pre[e.pto]=i;
					if(!inq[e.pto]){inq[e.pto]=1;q[++r]=e.pto;}
				}
			}
		}
		if(dis[T]==INF) break;
		cost+=dis[T];
		for(int i=pre[T];~i;i=pre[eg[i].pfr])
			eg[i].flo-=1,eg[i^1].flo+=1;
		int imp=eg[pre[T]].pfr;
		int npc=(imp-1)%m+1,kth=(imp-1)/m+1;
		for(int i=1;i<=n;i++)
			addEdge(m*sp+i,kth*m+npc,1,(kth+1)*mtx[i][npc]);
	}
	return cost;
}
int main()
{
	memset(head,-1,sizeof(head));
	int m,n; scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&peo[i]);
	for(int i=1;i<=n;i++) sp+=peo[i];
	S=m*sp+n+1;T=nds=S+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mtx[i][j]);
	for(int i=1;i<=n;i++)
		addEdge(S,m*sp+i,peo[i],0);
	for(int i=1;i<=m*sp;i++)
		addEdge(i,T,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
				addEdge(m*sp+i,j,1,mtx[i][j]);
	long long ans=maxflow(n,m);
	printf("%lld",ans);
}