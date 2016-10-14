#include <cstdio>
#include <cstring>
#define MAXN 205
int e[MAXN*MAXN],etop,head[MAXN],next[MAXN*MAXN];
int l[MAXN],r[MAXN];

bool vis[MAXN];
int match[MAXN];
int n,m;
inline bool sym(int a,int b)//symmetrical
{return a+b==(a|b) && (((a|b)+1)&(a|b))==0;}
void addedge(int p1,int p2)
{
	etop++;
	e[etop]=p2;
	next[etop]=head[p1];
	head[p1]=etop;
}
bool dfs(int p)
{
	for(int i=head[p];i!=0;i=next[i])
		if(vis[e[i]]==0)
		{
			vis[e[i]]=1;
			if(match[e[i]]==0 || dfs(match[e[i]])==1)
			{
				match[e[i]]=p;
				return 1;
			}
		}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&l[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&r[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(sym(l[i],r[j]))
				addedge(i,j);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(dfs(i)==1) ans++;
	}
	printf("%d",ans);
	return 0;
}
