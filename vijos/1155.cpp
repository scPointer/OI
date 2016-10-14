#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define MAXN 205
#define INF 1<<25
struct Point{int x0,y0;}pt[MAXN];
struct Node{
	double dis;
	int p;
//	Node(int p0,int dis0):p(p0),dis(dis0){}
	bool operator<(const Node oth)const{return dis>oth.dis;}
};
struct Edges{int pto;};
vector<int> ed;
vector<int> gp[MAXN];
void addedge(int p1,int p2)
{
	ed.push_back(p2);
	gp[p1].push_back(ed.size()-1);
}
double d[MAXN];
int frt[MAXN],vis[MAXN];
int n,m;
double dijkstra(int s,int t,int bans=0,int bant=0)
{
	priority_queue<Node> pq;
	for(int i=1;i<=n;i++) d[i]=INF;
	d[s]=0;frt[s]=s;
	pq.push((Node){0,s});
	while(!pq.empty())
	{
		Node x=pq.top();pq.pop();
		int p=x.p;
		if(vis[p]==1) continue;
		vis[p]=1;
		for(int i=0;i<gp[p].size();i++)
		{
			if(bans==p&&bant==ed[gp[p][i]]) continue;
			int pto=ed[gp[p][i]];
			double dist=sqrt((pt[p].x0-pt[pto].x0)*(pt[p].x0-pt[pto].x0)+(pt[p].y0-pt[pto].y0)*(pt[p].y0-pt[pto].y0));
			if(d[pto]>d[p]+dist)
			{
				d[pto]=d[p]+dist;
				frt[pto]=p;
				pq.push((Node){d[pto],pto});
			}
		}
	}
	return d[t];
}
void banedgesolve(int s,int t)
{
	int bans=frt[t],bant=t;
	double ans=INF;
	while(bans!=bant)
	{
		memset(d,0,sizeof(d));
		memset(vis,0,sizeof(vis));
		double ret=dijkstra(s,t,bans,bant);
		if(ret<INF-1&&ret<ans) ans=ret;
		bant=bans;
		bans=frt[bans];
	}
	if(ans<INF-1) printf("%.02f",ans);
	else printf("-1");
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x0,y0;
		scanf("%d%d",&x0,&y0);
		pt[i].x0=x0;pt[i].y0=y0;
	}
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		addedge(p1,p2);
		addedge(p2,p1);
	}
	dijkstra(1,n);
	banedgesolve(1,n);
	return 0;
}
