#include <cstdio>
#include <algorithm>
#define N 15005
#define M 30005
#define Max(a,b) (a>b?a:b)
int fa[N][15],dmax[N][15];
struct Edge{int pfr,pto,dis;}eg[M];
int head[N],nxt[M*2],dis[M*2],e[M*2],h[N];
int dset[N];
bool cmp(Edge a,Edge b){return a.dis<b.dis;}
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
void setHead(int cnt)
{
	for(int i=1;i<=cnt;i++)
	{
		e[i*2-1]=eg[i].pto;
		nxt[i*2-1]=head[eg[i].pfr];
		dis[i*2-1]=eg[i].dis;
		head[eg[i].pfr]=i*2-1;
		e[i*2]=eg[i].pfr;
		nxt[i*2]=head[eg[i].pto];
		dis[i*2]=eg[i].dis;
		head[eg[i].pto]=i*2;
	}
}
void setTree(int p)
{
	for(int i=head[p],pt;i;i=nxt[i])
		if(e[i]!=fa[p][0])
		{
			pt=e[i];
			fa[pt][0]=p;
			dmax[pt][0]=dis[i];
			h[pt]=h[p]+1;
			setTree(pt);
		}
}
int query(int p1,int p2)
{
	if(h[p1]<h[p2]) std::swap(p1,p2);
	int delta=h[p1]-h[p2];
	int res=0;
	for(int i=0;i<15;i++)
		if((1<<i)&delta)
		{
			res=Max(res,dmax[p1][i]);
			p1=fa[p1][i];
		}
	for(int i=14;i>=0;i--)
		if(fa[p1][i]!=fa[p2][i])
		{
			res=Max(res,dmax[p1][i]);
			res=Max(res,dmax[p2][i]);
			p1=fa[p1][i];
			p2=fa[p2][i];
		}
	if(p1!=p2) res=Max(res,Max(dmax[p1][0],dmax[p2][0]));
	return res;
}
int main()
{
	int n,m,Q;
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&eg[i].pfr,&eg[i].pto,&eg[i].dis);
	std::sort(eg+1,eg+1+m,cmp);
	for(int i=1;i<=n;i++) dset[i]=i;
	
	int ueg=0;
	for(int i=1,f1,f2;i<=m;i++)
	{
		f1=find(eg[i].pfr);f2=find(eg[i].pto);
		if(f1!=f2)
		{
			dset[f1]=f2;
			eg[++ueg]=eg[i];
		}
	}
	setHead(ueg);
	fa[1][0]=1;h[1]=1;
	setTree(1);
	for(int i=1,j=1; j<=n; i++,j<<=1)
		for(int k=1;k<=n;k++)
		{
			fa[k][i]=fa[fa[k][i-1]][i-1];
			dmax[k][i]=Max(dmax[k][i-1],dmax[fa[k][i-1]][i-1]);
		}
	for(int i=1,p1,p2;i<=Q;i++)
	{
		scanf("%d%d",&p1,&p2);
		printf("%d\n",query(p1,p2));
	}
}
