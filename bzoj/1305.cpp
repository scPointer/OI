#include <cstdio>
#define Min(a,b) (a<b?a:b)
#define N 205
#define M 6005
struct Edge{int pfr,pto,flo,lim;}eg[M];
int head[N],nxt[M],egtot;
int marka[N],markb[N];
int S,T,nds;

int q[N],stg[N],hd[N];
void addEdge(int p1,int p2,int flo)
{
	eg[egtot]=(Edge){p1,p2,0,flo};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot]=(Edge){p2,p1,0,0};
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
bool markStage()
{
	int l,r,p;
	for(int i=1;i<=nds;i++) stg[i]=-1;
	stg[S]=1;q[l=r=1]=S;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];~i;i=nxt[i])
		{
			Edge& e=eg[i];
			if(e.flo<e.lim && stg[e.pto]==-1)
				stg[e.pto]=stg[p]+1,q[++r]=e.pto;
		}
	}
	return stg[T]!=-1;
}
int dinic(int p,int a)
{
	if(p==T || a==0) return a;
	int flow=0,f;
	for(;~hd[p];hd[p]=nxt[hd[p]])
	{
		Edge& e=eg[hd[p]];
		if(stg[e.pto]==stg[p]+1 && (f=dinic(e.pto,Min(a,e.lim-e.flo)))>0)
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
void Maxflow()
{
	while(markStage())
	{
		for(int i=1;i<=nds;i++) hd[i]=head[i];
		dinic(S,1<<20);
	}
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	S=n*4+1;T=n*4+2;nds=n*4+2;
	for(int i=1;i<=nds;i++) head[i]=-1;
	for(int i=1;i<=n;i++)
	{
		marka[i]=egtot;
		addEdge(S,i,0);
		markb[i]=egtot;
		addEdge(i+n,T,0);
	}
	for(int i=1;i<=n;i++)
		addEdge(i,i+n*2,k),addEdge(i+n*3,i+n,k);
	char cr;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			while( (cr=getchar())!='Y' && cr!='N');
			cr=='Y'? addEdge(i,j+n,1): addEdge(i+n*2,j+n*3,1);
		}
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=n;j++)
			eg[marka[j]].lim++,eg[markb[j]].lim++;
		Maxflow();
		bool iffail=false;
		for(int j=1;j<=n;j++)
			if(eg[marka[j]].lim!=eg[marka[j]].flo)
			{iffail=true;break;}
		if(iffail){printf("%d",i-1);break;}
	}
	return 0;
}
