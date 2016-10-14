#include <cstdio>
#define MAXN 3005
#define MAXM 8005
#define MAXI 100000000
#defien MIN(a,b) (a<b?a:b)
struct Edge{
	int pto;
	int next;
}ed[MAXM];
int head[MAXN],tail[MAXN],edtop;
int ind[MAXN];
int vis[MAXN];
int stack[MAXN],tops;
int instack[MAXN];
int pr[MAXN];

int w[MAXN];
int n,person,m,cost;
void addedge(int p1,int p2)
{
	edtop++;
	ed[edtop].pto=p2;
	ed[edtop].next=head[p1];
	head[p1]=edtop;
	if(tail[p1]==0) tail[p1]=edtop;
	ind[p2]++;
}
void dfs(int p,int v)
{
	vis[p]=v;
	int k=head[p];
	while(ed[k].pto!=0)
	{
		if(vis[ed[k].pto]==0)
			dfs(vis[ed[k].pto],v);
		k=ed[k].next;
	}
}
int dfs_circle(int p,int v)
{
	vis[p]=v;
	int k=head[p],ans=MAXI;
	if(w[p]>=0) ans=w[p];
	while(ed[k].pto!=0)
	{
		if(vis[ed[k].pto]==0)
		{
			int ret=dfs_circle(vis[ed[k].pto]);
			ans=MIN(ans,ret);
		}
		k=ed[k].next;
	}
	return ans;
}
void tarjan(int p,int starttime)
{
	tops++;
	stack[tops]=p;
	instack[p]=tops;
	vis[p]=1;
	int k=head[p];
	while(ed[k].pto!=0)
	{
		int kt=ed[k].pto;
		if(vis[kt]==0)
			tarjan(kt);
		else if(instack[kt]>starttime)
		{
			for(int tn=tops;pr[stack[tn]]!=kt&&tn>starttime;tn--)
			{
				pr[stack[tn]]=kt;
				
		}
		k=ed[k].next;
	}
	stack[tops]=0;
	instack[p]=0;
	tops--;
}
int main()
{
	scanf("%d%d",&n,&person);
	for(int i=1;i<=n;i++)
	{w[i]=-1;pr[i]=i;}
	for(int i=1;i<=person;i++)
	{
		int p,fund;
		scanf("%d%d",&p.&fund);
		w[p]=fund;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		addedge(p1,p2);
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==0)
			tarjan(i,tops);
	bool fail=0;
	for(int i=1;i<=n;i++)
		if(ind[i]==0)
		{
			if(w[i]>=0)
			{dfs(i,1);cost+=w[i];}
			else
//				dfs(i,-1);
			{fail=1;break;}	
		}
	if(fail==1)
	{
		control_all();
		print_min();
	}
	else
	{
		int count_circle=1;
		for(int i=1;i<=n;i++)
			if(vis[i]==0)
			{
				int ans=dfs_circle(i,++count_circle);
				if(ans==MAXI)
					dfs_del(i,count_circle);
				else cost+=ans;
			}
	}
	return 0;
}
