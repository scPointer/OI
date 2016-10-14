#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXB 15
#define MAXN 10005
struct Edge{
	int pto,next;
	long long dis;
}ed[MAXN*2];
int head[MAXN],edtop;

int dad[MAXN][MAXB],h[MAXN];
long long d[MAXN][MAXB];
int vis[MAXN],queue[MAXN];

int n,m;
void addedge(int p1,int p2,long long dist)
{
	edtop++;
	ed[edtop].pto=p2;
	ed[edtop].dis=dist;
	ed[edtop].next=head[p1];
	head[p1]=edtop;
}
void settree()
{
	dad[1][0]=1;
	int l,r;
	queue[l=r=1]=1;
	while(l<=r)
	{
		int p=queue[l++];
		vis[p]=1;
		for(int i=1;i<MAXB;i++)
		{
			dad[p][i]=dad[dad[p][i-1]][i-1];
			d[p][i]=d[p][i-1]+d[dad[p][i-1]][i-1];
		}
		for(int i=head[p];ed[i].pto!=0;i=ed[i].next)
			if(vis[ed[i].pto]==0)
			{
				h[ed[i].pto]=h[p]+1;
				dad[ed[i].pto][0]=p;
				d[ed[i].pto][0]=ed[i].dis;
				queue[++r]=ed[i].pto;
			}
	}
}
long long lca(int p1,int p2)
{
	long long sum=0;
	if(h[p1]<h[p2]) swap(p1,p2);
	for(int i=MAXB-1;i>=0;i--)
	{
		if(h[dad[p1][i]]>=h[p2])
		{
			sum+=d[p1][i];
			p1=dad[p1][i];
		}
	}
	return p1==p2?sum:-1;
}
int main()
{
	memset(d,0,sizeof(d));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++)
	{
		int p1,p2;
		long long dist;
		scanf("%d%d%lld",&p1,&p2,&dist);
//		cin>>p1>>p2>>dist;
		addedge(p1,p2,dist);
		addedge(p2,p1,dist);
	}
	settree();
	long long sumdist=0;
	int count=0;
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		long long ret=lca(p1,p2);
		if(ret>0)
		{
			count++;
			sumdist+=ret;
		}
	}
	printf("%d\n%I64d",count,sumdist);
//	cout<<count<<endl<<sumdist;
	return 0;
}
