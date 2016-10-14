#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXT 1005
#define INF 1073741823
struct Edge{int pfr,pto,lim,flo,cst;};
vector<Edge> ed;
vector<int> gp[MAXT];

int inq[MAXT],d[MAXT],p[MAXT],a[MAXT];
int t,n,k;
void addedge(int t1,int t2,int limit,int cost)
{
	ed.push_back((Edge){t1,t2,limit,0,cost});
	ed.push_back((Edge){t2,t1,0,0,-cost});
	int sz=ed.size();
	gp[t1].push_back(sz-2);
	gp[t2].push_back(sz-1);
}
bool LCA(int s,int t,int& flow,int& cost)
{
	for(int i=1;i<=t+1;i++) d[i]=INF;
	memset(inq,0,sizeof(inq));
	inq[s]=1;d[s]=0;a[s]=INF;p[s]=-1;
	queue<int> q;
	q.push(s);
	while(q.empty()==0)
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
//		printf("u=%d\n",u);
		for(int i=gp[u].size()-1;i>=0;i--)
		{
			Edge& e=ed[gp[u][i]];
			if(e.lim>e.flo && d[e.pto]>d[u]+e.cst)
			{
				
//				printf("%d>%d+%d",d[e.pto],d[u],e.cst);
//				printf("fr%d to%d\n",e.pfr,e.pto);
//				printf("d[%d]>d[%d]+%d  q%d\n",e.pto,u,e.cst,q.size());
				d[e.pto]=d[u]+e.cst;
				p[e.pto]=gp[u][i];
				a[e.pto]=min(a[u],e.lim-e.flo);
				if(inq[e.pto]==0){q.push(e.pto);inq[e.pto]=1;}
			}
		}
	}
//	printf("flow%d cost%d\n",flow,cost);
	if(d[t]==INF) return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	int u=p[t];
	while(u!=-1)
	{
		ed[u].flo+=a[t];
		ed[u^1].flo-=a[t];
//		printf("fr %d to %d lim %d flo %d cst %d\n",ed[u].pfr,ed[u].pto,ed[u].lim,ed[u].flo,ed[u].cst);
		u=p[ed[u].pfr];
	}
	return true;
}
int mincost(int s,int t)
{
	int flow=0,cost=0;
	while(LCA(s,t,flow,cost)) ;
	return cost;
}
int main()
{
	scanf("%d%d%d",&t,&n,&k);
	for(int i=0;i<=t;i++)
		addedge(i,i+1,k,0);
	for(int i=1;i<=n;i++)
	{
		int t1,t2,cost;
		scanf("%d%d%d",&t1,&t2,&cost);
		addedge(t1,t2+1,1,-cost);
	}
	int ans=mincost(0,t+1);
	printf("%d",-ans);
	return 0;
}
