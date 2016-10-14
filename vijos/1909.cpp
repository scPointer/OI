#include <cstdio>
#define MAXM 200001
#define MAXN 10001
#define INF 9999999
#define min(a,b) (a<b?a:b)
struct edge{
	int pto;
	int next;
}ed[MAXM],ed2[MAXM];
int head[MAXN],edtop;
int head2[MAXN],edtop2;
//int reach[MAXN];
int vis[MAXN];
int del[MAXN];
int queue[MAXN];
int dis[MAXN];
int inqueue[MAXN];
int n,m,s,t;
void addedge2(int p1,int p2)
{
	edtop2++;
	ed2[edtop2].pto=p2;
	ed2[edtop2].next=head2[p1];
	head2[p1]=edtop2;
	
//	edtop++;
//	ed[edtop].pto=p1;
//	ed[edtop].next=head[p2];
//	head[p2]=edtop;
}
void addedge(int p1,int p2)
{
	edtop++;
	ed[edtop].pto=p2;
	ed[edtop].next=head[p1];
	head[p1]=edtop;
	
//	edtop++;
//	ed[edtop].pto=p1;
//	ed[edtop].next=head[p2];
//	head[p2]=edtop;
}
int lca(int p)
{
	for(int i=0;i<=MAXN-1;i++)
		dis[i]=INF;
	dis[p]=0;
//	int ans=INF;
	int st=0,end=0;
	queue[st++]=p;
	while(st!=end)
	{
		int k=head[queue[end]];
		int kd=queue[end];
		while(ed[k].pto!=0)
		{
			int q=ed[k].pto;
			if(del[q]==1){k=ed[k].next;continue;}
			if(dis[q]>dis[kd]+1)
			{
				dis[q]=dis[kd]+1;
				if(inqueue[q]==0)
				{
					inqueue[q]=1;
					queue[st]=q;
					st=(st+1)%MAXN;
				}
			}
			k=ed[k].next;
		}
		end=(end+1)%MAXN;
	}
	return dis[s];
}
bool allreach(int p)
{
	int k=head2[p];
	if(ed2[k].pto==0&&p!=t) return 0;
	while(ed2[k].pto!=0)
	{
		int q=ed2[k].pto;
		if(vis[q]==0)
			return 0;
		k=ed2[k].next;
	}
	return 1;
}
void dfs(int p)
{
	vis[p]=1;
	int k=head[p];
	while(ed[k].pto!=0)
	{
		int q=ed[k].pto;
		if(vis[q]==0)
			dfs(q);
		k=ed[k].next;
	}
}
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		if(p1!=p2)
		{
			addedge(p2,p1);
			addedge2(p1,p2);
		}
	}
	scanf("%d%d",&s,&t);
}
int main()
{
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
	init();
	dfs(t);
	for(int i=1;i<=n;i++)
		if(allreach(i)==0) del[i]=1;
	int ans=lca(t);
	if(ans==INF) printf("-1");
	else printf("%d",ans);
	return 0;
}
