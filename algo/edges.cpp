#include <cstdio>
#define N 100050
#define M 200050
struct Edge{
	int pfr,pto,wi;
}eg[M];
int head[N],next[M],egtot;
void addEdge(int pfr,int pto,int wi)
{
	++egtot;
	eg[egtot].pfr=pfr;
	eg[egtot].pto=pto;
	eg[egtot].wi=wi;
	next[egtot]=head[pfr];
	head[pfr]=egtot;
}
void spfa()
{
	......
	
	for(int e=head[p];e;e=next[e])
	{
		if(dis[eg[e].pfr]>dis[eg[e].pto]+eg[e].wi)
		{
			dis[eg[e].pfr]=dis[eg[e].pto]+eg[e].wi;
			
		}
	}
	......
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,p1,p2,w;i<=m;i++)
	{
		scanf("%d%d%d",&p1,&p2,&w);
		addEdge(p1,p2,w);
	}
}