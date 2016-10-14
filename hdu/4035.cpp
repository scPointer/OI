#include <cstdio>
#include <cstring>
#define clr(a) memset(a,0,sizeof(a));
#define N 10005
#define eps 1e-9
int eg[N*2],nxt[N*2],head[N],egtot;
int deg[N];
double ai[N],bi[N],ci[N],ki[N],mi[N];
int n;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
	deg[p1]++;
}
void dfs(int p,int fa)
{
	if(deg[p]==1 && p!=1)
	{
		ai[p]=ki[p];
		bi[p]=mi[p];
		ci[p]=mi[p];
		return;
	}
	double suma=0,sumb=0,sumc=0;
	for(int i=head[p],pt;i;i=nxt[i])
		if(eg[i]!=fa)
		{
			pt=eg[i];
			dfs(pt,p);
			suma+=ai[pt];
			sumb+=bi[pt];
			sumc+=ci[pt];
		}
	sumb=(1-mi[p]/deg[p]*sumb);
	ai[p]=(ki[p]+mi[p]/deg[p]*suma)/sumb;
	bi[p]=(mi[p]/deg[p])/sumb;
	ci[p]=(mi[p]/deg[p]*sumc+mi[p])/sumb;
}
void init()
{
	clr(head);clr(deg);
	egtot=0;
	clr(ai);clr(bi);clr(ci);clr(ki);clr(mi);
	scanf("%d",&n);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	for(int i=1,kk,ee;i<=n;i++)
	{
		scanf("%d%d",&kk,&ee);
		ki[i]=kk/100.0;mi[i]=(100-kk-ee)/100.0;
	}
}
int main()
{
	int T; scanf("%d",&T);
	for(int cas=1;cas<=T;cas++)
	{
		init();
		dfs(1,0);
		printf("Case %d: ",cas);
		if(1-ai[1]<eps) printf("impossible\n");
		else printf("%.6lf\n",ci[1]/(1-ai[1]));
	}
}