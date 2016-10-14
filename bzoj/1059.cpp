#include <cstdio>
#define N 405
#define M 160005
#define Min(a,b) (a<b?a:b)
#define INF 1<<20
struct Edge{int pfr,pto,flo,lim;}eg[M];
int head[N],nxt[M],egtot;
int hd[N],stg[N],que[N];
int nds,gt;
inline int RD(){static int res;scanf("%d",&res);return res;}
void addEdge(int p1,int p2)
{
//	printf("add%d %d\n",p1,p2);
	eg[egtot++]=(Edge){p1,p2,0,1};
	nxt[egtot-1]=head[p1];
	head[p1]=egtot-1;
	eg[egtot++]=(Edge){p2,p1,0,0};
	nxt[egtot-1]=head[p2];
	head[p2]=egtot-1;
}
int maxflow(int p,int a)
{
//	printf("in%d a%d\n",p,a);
	if(p==gt || a==0) return a;
	int f,flow=0;
	for(;hd[p]!=-1;hd[p]=nxt[hd[p]])
	{
		Edge& e=eg[hd[p]];
		if(stg[e.pfr]+1==stg[e.pto] && (f=maxflow(e.pto,Min(e.lim-e.flo,a)))>0 )
		{
			flow+=f;
			a-=f;
			eg[hd[p]].flo+=f;
			eg[hd[p]^1].flo-=f;
			if(a==0) break;
		}
	}
	return flow;
}
bool markstage(int s,int t)
{
	for(int i=1;i<=nds;i++) stg[i]=-1;
	stg[s]=0;
	int l=1,r=1,p;que[1]=s;
	while(l<=r)
	{
		p=que[l++];
		for(int i=head[p];i!=-1;i=nxt[i])
		{
			Edge& e=eg[i];
			if(e.flo<e.lim && stg[e.pto]==-1)
				stg[e.pto]=stg[p]+1,que[++r]=e.pto;
		}
	}
	return stg[t]!=-1;
}
int dinic(int s,int t)
{
	int flow=0;
	while(markstage(s,t))
	{
		for(int i=1;i<=nds;i++) hd[i]=head[i];
		flow+=maxflow(s,INF);
	}
	return flow;
}
int main()
{
	for(int T=RD(),n;T;T--)
	{
		n=RD();gt=nds=n*2+2;
		for(int i=1;i<=nds;i++) head[i]=-1;
		egtot=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(RD()==1)
					addEdge(i,j+n);
		for(int i=1;i<=n;i++)
			addEdge(n*2+1,i),addEdge(i+n,n*2+2);
		if(dinic(n*2+1,n*2+2)==n)
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
