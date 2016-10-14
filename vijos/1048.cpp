#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 51

struct spirit{
	int val;
	int agst;
}spi[MAXN];
struct edge{
	int pto;
	int next;
}ed[MAXN*MAXN*2];
int edtop;
int n,ans;
int used[MAXN];
bool cmp(spirit a,spirit b)
{
	return a.val>b.val;
}
void dfs(int k,int qlt)
{
//	used[k]=1;
	qlt+=spi[k].val;
	if(qlt>ans) ans=qlt;
	if(k==n) return;
	
	int p=spi[k].agst;
	while(ed[p].pto!=0)
	{
		used[ed[p].pto]--;
		p=ed[p].next;
	}
	
	int maxqlt=qlt;
	for(int i=k+1;i<=n;i++)
		if(used[i]>=0) maxqlt+=spi[i].val;
	
	if(maxqlt>qlt&&maxqlt>ans)
	{
		for(int i=k+1;i<=n;i++)
			if(used[i]>=0) dfs(i,qlt);
	}
	
	p=spi[k].agst;
	while(ed[p].pto!=0)
	{
		used[ed[p].pto]++;
		p=ed[p].next;
	}
}
void ReadInEdge(int s,int d)
{
	edtop++;
	ed[edtop].pto=d;
	ed[edtop].next=spi[s].agst;
	spi[s].agst=edtop;
	
	edtop++;
	ed[edtop].pto=s;
	ed[edtop].next=spi[d].agst;
	spi[d].agst=edtop;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&spi[i].val);
	int s,d;
	while(scanf("%d%d",&s,&d)==2)
		ReadInEdge(s,d);
//	sort(spi+1,spi+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		memset(used,0,sizeof(used));
		dfs(i,0);
	}
	printf("%d",ans);
	return 0;
}
