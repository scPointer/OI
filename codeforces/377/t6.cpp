#include <cstdio>
#define N 800005
#define M 800005
int pfr[M],pto[M],nxt[M],head[N],egtot;
bool used[M],vis[N];
int dir[M];
int fa[N];
int dset[N];
int sum[N];
int pre[N];
int mx;
int dfind(int p){return dset[p]==p? p: dset[p]=dfind(dset[p]);}
void addEdge(int p1,int p2)
{
	pfr[egtot]=p1;
	pto[egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}
inline void merge(int p1,int p2)
{
	int f1=dfind(p1);
	int f2=dfind(p2);
	if(f1!=f2)
	{
		dset[f1]=f2;
		sum[f2]+=sum[f1];
	}
}
void dfs(int p)
{
	vis[p]=1;
	for(int e=head[p];~e;e=nxt[e])
		if(!used[e>>1])
		{
			used[e>>1]=1;
			int pt=pto[e];
			if(vis[pt] && dfind(p)!=dfind(pt))
			{
				for(int j=p;j!=pt && dfind(j)!=dfind(pt);j=fa[j])
				{
					merge(j,fa[j]);
//					dir[pre[j]]=1;
//					dir[pre[j]^1]=-1;
				}
				dir[e]=1;
				dir[e^1]=-1;
			}
			else if(!vis[pt])
			{
				fa[pt]=p;
				pre[pt]=e;
				dir[e]=1;
				dir[e^1]=-1;
				dfs(pt);
			}
			else
			{
				dir[e]=1;
				dir[e^1]=-1;
			}
		}
}
void dfs2(int p)
{
	vis[p]=1;
	for(int e=head[p];~e;e=nxt[e])
	{
		int pt=pto[e];
		if(dfind(pt)!=mx && !vis[pt])
		{
			dir[e]=-1;
			dir[e^1]=1;
			dfs2(pt);
		}
	}
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		head[i]=-1,dset[i]=i,sum[i]=1;
	for(int i=1,p1,p2;i<=m;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	dfs(1);
	mx=0;
	int ans=0;
	for(int i=1;i<=n;i++)
		if(sum[i]>ans)
			ans=sum[i],mx=i;
	for(int i=1;i<=n;i++)
		vis[i]=fa[i]=0;
	for(int i=1;i<=n;i++)
		if(dfind(i)==mx)
			dfs2(i);
	printf("%d\n",ans);
	for(int i=0;i<egtot;i+=2)
	{
		if(dir[i]>=0)
			printf("%d %d\n",pfr[i],pto[i]);
		else
			printf("%d %d\n",pto[i],pfr[i]);
	}
}
