#include <cstdio>
#define N 205
#define M 20005
struct Edge{
	int pfr,pto;
	bool dir;
}eg[M<<1];
int nxt[M<<1],head[N],egtot;
int realEdges;
int deg[N];
int n;
void addEdge(int p1,int p2)
{
	deg[p1]++;
	eg[egtot]=(Edge){p1,p2,0};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}
void init()
{
	realEdges=egtot=0;
	for(int i=1;i<=n;i++)
		head[i]=-1,deg[i]=0;
}
void dfs(int p)
{
	while(head[p]!=-1 && eg[head[p]^1].dir==1)
		head[p]=nxt[head[p]];
	if(head[p]==-1) return;
	eg[head[p]].dir=1;
	int pto=eg[head[p]].pto;
//	printf("marked %d %d\n",p,pto);
	head[p]=nxt[head[p]];
	dfs(pto);
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int m;scanf("%d%d",&n,&m);
		init();
		for(int i=1;i<=m;i++)
		{
			int p1,p2;scanf("%d%d",&p1,&p2);
			addEdge(p1,p2);
			addEdge(p2,p1);
		}
		realEdges=egtot;
		
		int ans=0,lastodd=0;
		for(int i=1;i<=n;i++)
			if(deg[i]&1)
			{
				if(lastodd)
				{
					addEdge(i,lastodd);
					addEdge(lastodd,i);
					lastodd=0;
				}else lastodd=i;
			}else ans++;
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			dfs(i);
		
		for(int i=0;i<realEdges;i++)
			if(eg[i].dir)
				printf("%d %d\n",eg[i].pfr,eg[i].pto);
	}
}
