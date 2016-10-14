#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 1<<22
#define N 1005
#define M N*N*15
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
int match[N];
struct Edge{int pfr,pto,flo,lim,nxt;}eg[M];
int head[N],etot;
int nl,nr,m,n;
void addedge(int p1,int p2)
{
	eg[etot]=(Edge){p1,p2,0,1,head[p1]};
//	printf("addedge %d %d %d %d %d\n",p1,p2,0,1,head[p1]);
	head[p1]=etot++;
	eg[etot]=(Edge){p2,p1,0,0,head[p2]};
//	printf("addedge %d %d %d %d %d\n",p2,p1,0,0,head[p2]);
	head[p2]=etot++;
}
int d[N],pre[N],hd[N],t;
int q[N];
bool markstage(int s,int t)
{
	memset(d,0,sizeof(d));
	int l=1,r=1;
	d[s]=1;q[1]=s;
	while(l<=r)
	{
		int p=q[l++];
		for(int i=head[p];i!=-1;i=eg[i].nxt)
		{
			Edge& e=eg[i];
			if(!d[e.pto] && e.flo<e.lim)
			{
				d[e.pto]=d[p]+1;
				q[++r]=e.pto;
			}
		}
	}
//	printf("STAGE\n");
//	for(int i=1;i<=n;i++) printf("stage %d]=%d\n",i,d[i]);
	return d[t];
}
int maxflow(int p,int a)
{
	if(p==t || a==0) return a;
	int flow=0,f;
	for(hd[p]?:hd[p]=head[p];hd[p]!=-1;hd[p]=eg[hd[p]].nxt)
	{
		Edge& e=eg[hd[p]];
		if(d[e.pto]==d[p]+1 && (f=maxflow(e.pto,min(a,e.lim-e.flo))))
		{
//			printf("flo %d from %d to %d\n",f,e.pfr,e.pto);
			flow+=f;
			a-=f;
			e.flo+=f;
			eg[hd[p]^1].flo-=f;
			if(a==0) break;
		}
	}
	return flow;
}
int dinic(int n,int s,int t)
{
	int flow=0;
	while(markstage(s,t))
	{
		memset(hd,0,sizeof(hd));
		flow+=maxflow(s,INF);
	}
	return flow;
}
int main()
{
	nl=RD();nr=RD();m=RD();n=nl+nr+2;
	memset(head,-1,sizeof(head));
	int boy,girl;
	for(int i=1;i<=m;i++)
	{
		boy=RD();girl=RD()+nl;
		addedge(boy,girl);
	}
	for(int i=1;i<=nl;i++) addedge(n-1,i);
	for(int i=1;i<=nr;i++) addedge(i+nl,n);
	t=n;int ans=dinic(n,n-1,n);
	for(int i=0;i<=etot;i++)
		if(eg[i].pfr<=nl && eg[i].pto>nl && eg[i].pto<=nl+nr && eg[i].flo>0)
			match[eg[i].pfr]=eg[i].pto-nl;
	printf("%d\n",ans);
	for(int i=1;i<=nl;i++)
		printf("%d ",match[i]);
	return 0;
}
