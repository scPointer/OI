#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 10005
#define MAXM 50005
#define MAXW 150000
#define MAXL 15
struct Edge{
	int p1,p2,w,next;
}readedge[MAXM*2],edge[MAXM*2];
int head[MAXN],edtop;
int n,m,q;

int dset[MAXN];

bool vis[MAXN];
int h[MAXN];
int fd[MAXN][MAXL];
int Fmin[MAXN][MAXL];
bool cmp(Edge a,Edge b){return a.w>b.w;}
void addedge(int p1,int p2,int w)
{
	edtop++;
	edge[edtop].p2=p2;
	edge[edtop].w=w;
	edge[edtop].next=head[p1];
	head[p1]=edtop;
}
int find(int p)
{
	return dset[p]==p?p:dset[p]=find(dset[p]);
}
void settree(int p)
{
	vis[p]=1;
	int k=head[p];
	while(edge[k].p2!=0)
	{
		if(vis[edge[k].p2]==0)
		{
			int kp=edge[k].p2;
			fd[kp][0]=p;
			Fmin[kp][0]=edge[k].w;
			h[kp]=h[p]+1;
			settree(kp);
		}
		k=edge[k].next;
	}
}
int func2(int& p,int hei)
{
	int d=MAXL-1;
	int ret=MAXW;
	while(1)
	{
		while(h[fd[p][d]]<hei) d--;
		ret=min(ret,Fmin[p][d]);
		p=fd[p][d];
		if(h[p]==hei) break;
	}
	return ret;
}
int function(int p1,int p2)
{
	if(find(p1)!=find(p2)) return -1;
	if(p1==p2) return 0;
	int smin;
	if(h[p1]!=h[p2]) smin=h[p1]>h[p2]?func2(p1,h[p2]):func2(p2,h[p1]);
	else smin=MAXW;
	if(p1==p2) return smin;
	for(int d=MAXL-1;d>=0;d--)
	{
		if(fd[p1][d]!=fd[p2][d])
		{
			smin=min(smin,min(Fmin[p1][d],Fmin[p2][d]));
			p1=fd[p1][d];p2=fd[p2][d];
		}
	}
	smin=min(smin,min(Fmin[p1][0],Fmin[p2][0]));
	return smin;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		dset[i]=i;
	for(int i=1;i<=m;i++)
	{
		int p1,p2,w;
		scanf("%d%d%d",&p1,&p2,&w);
		readedge[i].p1=p1;
		readedge[i].p2=p2;
		readedge[i].w=w;
	}
	sort(readedge+1,readedge+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		int f1=find(readedge[i].p1);
		int f2=find(readedge[i].p2);
		if(f1!=f2)
		{
			dset[f1]=f2;
			addedge(readedge[i].p1,readedge[i].p2,readedge[i].w);
			addedge(readedge[i].p2,readedge[i].p1,readedge[i].w);
		}
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==0)
		{
			fd[i][0]=i;
			Fmin[i][0]=MAXW;
			settree(i);
		}
	for(int i=1;i<=MAXL-1;i++)
		for(int j=1;j<=n;j++)
		{
			fd[j][i]=fd[fd[j][i-1]][i-1];
			Fmin[j][i]=min(Fmin[j][i-1],Fmin[fd[j][i-1]][i-1]);
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		printf("%d\n",function(p1,p2));
	}
	return 0;
}
