#include <cstdio>
#include <cstring>
#define N 5005
#define M 50005
#define INF 100000
#define EDGE ((N+M+M*2)*5)
#define NODE (N+M)
#define Min(a,b) ((a)<(b)?(a):(b))
struct Edge{int pfr,pto,lim,flo,nxt;}eg[EDGE];
int head[EDGE],etot;
int n,m,node,S,T,sumprofit;

int stg[NODE],q[NODE];
int hd[NODE];
inline int RD()
{
	static char cr;
	static int res;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
void AddEdge(int p1,int p2,int lim)
{
	eg[etot++]=(Edge){p1,p2,lim,0,head[p1]};
	head[p1]=etot-1;
	eg[etot++]=(Edge){p2,p1,0,0,head[p2]};
	head[p2]=etot-1;
}
bool MarkStage(int s,int t)
{
	for(int i=1;i<=node;i++) stg[i]=0;
	int l=1,r=1;
	q[1]=s;stg[s]=1;
	while(l<=r)
	{
		int p=q[l++];
		for(int i=head[p];~i;i=eg[i].nxt)
		{
			Edge& e=eg[i];
			if(e.flo<e.lim && !stg[e.pto])
			{
				stg[e.pto]=stg[p]+1;
				q[++r]=e.pto;
			}
		}
	}
	
//	for(int i=1;i<=node;i++) printf("stg%d = %d\n",i,stg[i]);
	
	return stg[t]?1:0;
}
int Dinic(int p,int a)
{
	if(p==T || a==0) return a;
	int flow=0,f;
	for(;~hd[p];hd[p]=eg[hd[p]].nxt)
	{
		Edge& e=eg[hd[p]];
		if(stg[e.pto]==stg[p]+1 && (f=Dinic(e.pto,Min(a,e.lim-e.flo))))
		{
//			printf("flow %d: from %d to %d\n",f,p,e.pto);
			flow+=f;
			a-=f;
			eg[hd[p]].flo+=f;
			eg[hd[p]^1].flo-=f;
			if(!a) break;
		}
	}
	
	return flow;
}
int MaxFlow(int s,int t)
{
	int flow=0;
	while(MarkStage(s,t))
	{
		for(int i=1;i<=node;i++) hd[i]=head[i];
		flow+=Dinic(s,INF);
	}
	return flow;
}
int main()
{
	n=RD();m=RD();S=n+m+1;T=S+1;node=T;
	memset(head,-1,sizeof(head));
	
	for(int i=1;i<=n;i++) AddEdge(S,i,RD());
	for(int i=1,x,y,z;i<=m;i++)
	{
		x=RD();y=RD();z=RD();
		AddEdge(x,n+i,INF);
		AddEdge(y,n+i,INF);
		AddEdge(n+i,T,z);
		sumprofit+=z;
	}
	int flow=MaxFlow(S,T);
	printf("%d",sumprofit-flow);
	return 0;
}
