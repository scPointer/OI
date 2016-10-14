#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 1<<20
#define MAXN 105
#define MAXM 305
struct Edge{int pfr,pto,lim,flo;};
vector<Edge> ed;
vector<int> ltb[MAXN];
bool vis[MAXN];
int d[MAXN],cur[MAXN],q[MAXN];
int n,numofedge,m;
int s,t;

int cn;
bool BFS()
{
	memset(vis,0,sizeof(vis));
	int l=1,r=1;
	q[1]=s;d[s]=1;vis[s]=1;
	while(l<=r)
	{
		int p=q[l++];
		for(int i=0;i<ltb[p].size();i++)
		{
			Edge& e=ed[ltb[p][i]];
			if(vis[e.pto]==0&&e.lim>e.flo)
			{
				vis[e.pto]=1;
				q[++r]=e.pto;
				d[e.pto]=d[p]+1;
			}
		}
	}
	return vis[t];
}
int DFS(int p,int a)
{
	if(p==t||a==0) return a;
	int flow=0,f;
	for(int& i=cur[p];i<ltb[p].size();i++)
	{
		Edge& e=ed[ltb[p][i]];
//		printf("count:%d\n",++cn);
		if(d[e.pto]==d[p]+1 && (f=DFS(e.pto,min(a,e.lim-e.flo)))>0)
		{
//			printf("from %d to %d flows %d[lim %d]\n",p,e.pto,f,e.lim);
			e.flo+=f;
			ed[ltb[p][i]^1].flo-=f;
			flow+=f;
			a-=f;
			if(a==0) break;
		}
	}
	return flow;
}
int Maxflow(int sp,int tp)
{
	s=sp;t=tp;
	int flow=0;
	while(BFS())
	{
		memset(cur,0,sizeof(cur));
		flow+=DFS(s,INF);
	}
	return flow;
}
void addedge(int p1,int p2,int dis)
{
	ed.push_back((Edge){p1,p2,dis,0});
	ed.push_back((Edge){p2,p1,0,0});
	int k=ed.size();
	ltb[p1].push_back(k-2);
	ltb[p2].push_back(k-1);
}
int main()
{
	scanf("%d%d",&n,&numofedge);
	for(int i=1;i<=numofedge;i++)
	{
		int p1,p2,dis;
		scanf("%d%d%d",&p1,&p2,&dis);
		addedge(p1,p2,dis);
		addedge(p2,p1,dis);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int p;
		scanf("%d",&p);
		addedge(p,n+1,INF);
	}
	int ans=Maxflow(1,n+1);
	printf("%d",ans);
	return 0;
}
