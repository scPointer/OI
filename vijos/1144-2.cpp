#include <cstdio>
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)
#define MABS(a) (a>0?a:a*(-1))
#define MAXN 1505
int dad[MAXN],fson[MAXN],bro[MAXN];//dad first_son brother
int sign[MAXN];//minus plus
int order[MAXN],vis_time;
int v[MAXN];
int n,k;
void solve()
{
	for(int i=n;i>=1;i--)
	{
		if(sign[i]==-k)
		{
			sign[i]=k;
			if(MABS(sign[dad[i]])<MABS(sign[i]))
				sign[dad[i]]=sign[i]-1;
		}
	}
}
void dfs(int p)
{
	order[++vis_time]=p;
	int son=fson[p];
	while(son!=0)
	{
		dfs(son);
		son=bro[son];
	}
}
int findroot()
{
	for(int i=1;i<=n;i++)
		if(dad[i]==0) return i;
}
void init()
{
	k=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int id,vi,num,child;
		scanf("%d%d%d",&id,&vi,&num);
		v[id]=vi;
		while(--num>=0)
		{
			scanf("%d",&child);
			dad[child]=id;
			if(fson[id]==0) fson[id]=child;
			else{bro[child]=fson[id];fson[id]=child;}
		}
	}
}
int main()
{
	init();
	int root=findroot();
	dfs(root);
	solve();
	return 0;
}
