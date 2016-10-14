#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 501
struct edge{
	int sp;
	int ep;
	int cost;
	int used;
//	int next;
}ed[MAXN*MAXN];
int edtop;
//int head[MAXN];
int dset[MAXN];
int minused[MAXN*MAXN];
int n,m;
bool cmp(edge a,edge b)
{
	return a.cost<b.cost;
}
void readinedge(int c1,int c2,int co)
{
	edtop++;
	ed[edtop].sp=c1;
	ed[edtop].ep=c2;
	ed[edtop].cost=co;
//	ed[edtop].next=head[st];
//	head[st]=edtop;
}
int find(int p)
{
	if(p!=dset[p]) dset[p]=find(dset[p]);
	return dset[p];
}
int MST(bool ifmin)
{
	for(int i=1;i<=n;i++)
		dset[i]=i;
	int sets=n,ans=0;
	for(int i=1;i<=edtop&&sets>1;i++)
	{
		int spss=find(ed[i].sp);
		int epss=find(ed[i].ep);
		if(ed[i].used!=-1&&spss!=epss)
		{
			sets--;
			dset[spss]=epss;
			if(ifmin==1) minused[i]=1;
			ans+=ed[i].cost;
		}
	}
	if(sets>1) return -1;
	else return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int city1,city2,cost;
		scanf("%d%d%d",&city1,&city2,&cost);
		readinedge(city1,city2,cost);
//		readinedge(city2,city1,cost);
	}
	sort(ed+1,ed+edtop+1,cmp);
	int ans1=MST(1);
	if(ans1==-1)
		{printf("Cost: -1\nCost: -1\n");return 0;}
	int ans2=-1,countedge=0;
	for(int i=1;i<=edtop&&countedge<n-1;i++)
		if(minused[i]==1)
		{
			ed[i].used=-1;
			int re=MST(0);
			if(re!=-1)
			{
				if(ans2==-1) ans2=re;
				else if(ans2>re) ans2=re;
			}
			ed[i].used=0;
		}
	printf("Cost: %d\nCost: %d",ans1,ans2);
	return 0;
}
