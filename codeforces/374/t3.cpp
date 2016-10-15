#include <cstdio>
#define N 5005
#define INF 1000000007
int eg[N<<1],nxt[N<<1],head[N],len[N<<1],egtot;
void addEdge(int p1,int p2,int l)
{
	eg[++egtot]=p2;
	len[egtot]=l;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
typedef long long ll;
int dis[N][N];
int pre[N][N];
int deg[N];
int q[N];
int ans[N];
int n,m,T;
void init()
{
	int l,r,p;l=1;r=0;
	for(int i=2;i<=n;i++)
		if(deg[i]==0) q[++r]=i;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];i;i=nxt[i])
		{
			int pt=eg[i];
			if(--deg[pt]==0) q[++r]=pt;
		}
	}
}
void solve()
{
	init();
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			dis[i][j]=INF;
	dis[1][1]=0;
	int l,r,p;q[l=r=1]=1;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];i;i=nxt[i])
		{
			int pt=eg[i];
			for(int j=1;j<=n;j++)
				if(dis[pt][j]>dis[p][j-1]+len[i])
					dis[pt][j]=dis[p][j-1]+len[i],pre[pt][j]=p;
			if(--deg[pt]<=0) q[++r]=pt;
		}
	}
	for(int i=n;i>=1;i--)
		if(dis[n][i]<=T)
		{
			printf("%d\n",i);
			for(int p=n,j=i;p;p=pre[p][j--])
				ans[j]=p;
			for(int j=1;j<=i;j++)
				printf("%d ",ans[j]);
			return;
		}
	printf("0");
}
int main()
{
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=m;i++)
	{
		int p1,p2,len;scanf("%d%d%d",&p1,&p2,&len);
		addEdge(p1,p2,len);
		deg[p2]++;
	}
	solve();
}
