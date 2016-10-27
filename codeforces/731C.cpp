#include <cstdio>
#define N 200050
int eg[N<<1],nxt[N<<1],head[N],egtot;
int col[N];
int vis[N];
int cnt[N],tim[N],timetip;
int maxcolor;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
int dfs(int p)
{
	vis[p]=1;
	if(tim[col[p]]==timetip)
		cnt[col[p]]++;
	else
		tim[col[p]]=timetip,cnt[col[p]]=1;
	if(cnt[col[p]]>cnt[maxcolor])
		maxcolor=col[p];
	int sumnodes=1;
	for(int e=head[p];e;e=nxt[e])
		if(!vis[eg[e]])
		{
			int ret=dfs(eg[e]);
			sumnodes+=ret;
		}
	
	return sumnodes;
}
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&col[i]);
	for(int i=1,p1,p2;i<=m;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	
	int ans=0;
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			timetip++;
			maxcolor=0;
			int sumnodes=dfs(i);
			ans+=sumnodes-cnt[maxcolor];
		}
	printf("%d\n",ans);
	return 0;
}