#include <cstdio>
#include <algorithm>
#define N 100005
#define M 2000005
#define Swap(a,b) {_temp=a;a=b;b=_temp;}
int nxt[M],head[N],egtot;
bool reach[N],vis[N];
int dset[N];
int hei[N];
int q[N];
int n,m;
struct Edge{int pfr,pto,len;}eg[M];
bool cmp(Edge a,Edge b){return hei[a.pto]!=hei[b.pto]?hei[a.pto]>hei[b.pto]:a.len<b.len;}
void addEdge(int p1,int p2,int l)
{
	eg[++egtot]=(Edge){p1,p2,l};
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
int find(int p){return dset[p]?dset[p]=find(dset[p]):p;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&hei[i]);
	for(int i=1,p1,p2,l,_temp;i<=m;i++)
	{
		scanf("%d%d%d",&p1,&p2,&l);
		if(hei[p2]>hei[p1]) Swap(p1,p2)
		addEdge(p1,p2,l);
		if(hei[p2]==hei[p1]) addEdge(p2,p1,l);
	}
	int l,r,p;q[l=r=1]=1;reach[1]=1;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];i;i=nxt[i])
			if(!reach[eg[i].pto])
				reach[eg[i].pto]=1,q[++r]=eg[i].pto;
	}
	int ansc=r;
	long long ansd=0;
	int ecnt=0;
	for(int i=1;i<=egtot;i++)
		if(reach[eg[i].pfr] && reach[eg[i].pto])
			eg[++ecnt]=eg[i];
	std::sort(eg+1,eg+1+ecnt,cmp);
	for(int i=1,f1,f2;i<=ecnt;i++)
	{
		f1=find(eg[i].pfr);f2=find(eg[i].pto);
		if(f1!=f2)
		{
			ansd+=eg[i].len;
			dset[f1]=f2;
		}
	}
	printf("%d %lld",ansc,ansd);
}
