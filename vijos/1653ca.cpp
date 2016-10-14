#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 1073741823
#define MAXN 105*105*2
#define MAXE MAXN*8
#define POINT(a,b,c) (m*(a-1)+b+c*m*n)
#define SOURSE m*n*2+1
#define SINK m*n*2+2
struct Edge{int pfr,pto,lim,flo,cst,next;};
Edge ed[MAXE];
int head[MAXN],edtop;
int val[MAXN/2];
int n,m,k;
void addedge(int p1,int p2,int limit=k,int cost=0)
{
	ed[edtop++]=(Edge){p1,p2,limit,0,cost,head[p1]};
	head[p1]=edtop-1;//wrong: head[p1]=edtop;
	ed[edtop++]=(Edge){p2,p1,0,0,-cost,head[p2]};
	head[p2]=edtop-1;
}
int p[MAXN],d[MAXN],a[MAXN],inq[MAXN],q[MAXN];
bool bellmanford(int s,int t,int np,int& flow,int& cost)
{
	for(int i=1;i<=np;i++) d[i]=INF;//wrong: p[i]=INF;
	p[s]=-1;a[s]=INF;d[s]=0;inq[s]=1;
	int l=1,r=0;
	q[++r]=s;
	while(l<=r)
	{
		int u=q[l++];//wrong: u=q[++l];
		inq[u]=0;
		for(int i=head[u];i!=-1;i=ed[i].next)//wrong: i=ed[u].next
		{
			if(ed[i].lim>ed[i].flo && d[ed[i].pto]>d[u]+ed[i].cst)
			//wrong: if(d[ed[i].pto]>d[u]+ed[i].cst)
			{
				d[ed[i].pto]=d[u]+ed[i].cst;
				p[ed[i].pto]=i;
				a[ed[i].pto]=min(a[u],ed[i].lim-ed[i].flo);
				if(inq[ed[i].pto]==0){q[++r]=ed[i].pto;inq[ed[i].pto]=1;}
			}
		}
	}
	
//	printf("flow %d cost %d\n",a[t],a[t]*d[t]);
	if(d[t]==INF) return false;//wrong: if(d[t]=INF)
	flow+=a[t];
	cost+=a[t]*d[t];
	int agp=t;
	while(agp!=s)
	{
		ed[p[agp]].flo+=a[t];
		ed[p[agp]^1].flo-=a[t];
		agp=ed[p[agp]].pfr;
	}
	return true;
}
int mincost(int s,int t)
{
	int flow=0,cost=0;
	while(bellmanford(s,t,n*m*2+2,flow,cost));
	return cost;
}
int main()
{//wrong: add "int k,m,n;" here
	scanf("%d%d%d",&k,&m,&n);
	for(int i=1;i<=n*m;i++)
		scanf("%d",&val[i]);
	for(int i=1;i<=m*n*2+2;i++) head[i]=-1;//wrong: for(int i=1;i<=m*n*2;i++)
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)//wrong: for(int j=1;j<=m-1;j++)
		{
			addedge(POINT(i,j,0),POINT(i,j,1),1,-val[POINT(i,j,0)]);
			addedge(POINT(i,j,0),POINT(i,j,1));
			if(j+1<=m) addedge(POINT(i,j,1),POINT(i,j+1,0));
			if(i+1<=n) addedge(POINT(i,j,1),POINT(i+1,j,0));
		}
	addedge(SOURSE,POINT(1,1,0));
	addedge(POINT(n,m,1),SINK);//wrong: addedge(SINK,POINT(n,m,1));
	int ans=mincost(SOURSE,SINK);
	printf("%d",-ans);
	return 0;
}
