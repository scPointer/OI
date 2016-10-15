#include <cstdio>
#include <algorithm>
#define M 30005
#define N 10005
#define ERA 10000000000007ll
#define INF 1000000000000000000ll
#define Min(a,b) (a<b?a:b)
typedef long long ll;
ll es[M],eg[M],nxt[M],wi[M],head[N],egtot;
bool used[M];
void addEdge(int p1,int p2,ll w)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	es[egtot]=p1;
	wi[egtot]=w;
	head[p1]=egtot;
}
struct setEG{int p1,p2,id;ll w;}se[M],prt[M];
ll d[N],pre[N];
bool vis[N];
int n,m,L,s,t;
void dijk()
{
	int S=s;
	for(int i=0;i<=n;i++)
		vis[i]=0,d[i]=INF;
	d[S]=0;
	while(1)
	{
		int p=-1;
		for(int i=1;i<=n;i++)
			if(vis[i]==0 && d[i]<INF)
			{
				if(p==-1 || d[i]<d[p])
					p=i;
			}
		if(p==-1) break;
		vis[p]=1;
		for(int i=head[p];i;i=nxt[i])
			if(d[eg[i]]>d[p]+wi[i])
			{
				d[eg[i]]=d[p]+wi[i];
				pre[eg[i]]=i;
			}
	}
}
/*
void setone(int p1,int p2)
{
	dis1[p2]=Min(dis1[p2],dis1[p1]+1);
	dis1[p1]=Min(dis1[p1],dis1[p2]+1);
	dis1[p2]=Min(dis1[p2],dis1[p1]+1);
	dis1[p1]=Min(dis1[p1],dis1[p2]+1);
	dis2[p1]=Min(dis2[p1],dis2[p2]+1);
	dis2[p2]=Min(dis2[p2],dis2[p1]+1);
	dis2[p1]=Min(dis2[p1],dis2[p2]+1);
	dis2[p2]=Min(dis2[p2],dis2[p1]+1);
}
*/
int main()
{

	scanf("%d%d%d%d%d",&n,&m,&L,&s,&t);
	++s;++t;
	int ss=0;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		++u;++v;
		prt[i]=(setEG){u,v,i,w};
		if(w==0)
		{
			++ss;
			se[ss]=(setEG){u,v,i,0};
			addEdge(u,v,1);
			addEdge(v,u,1);
		}
		else
		{
			addEdge(u,v,(ll)w*ERA);
			addEdge(v,u,(ll)w*ERA);
		}
	}
	dijk();
	if(d[t]==INF || d[t]/ERA+d[t]%ERA>L){printf("NO");return 0;}
	for(int p=t;p!=s;p=es[pre[p]])
	{
		int e=pre[p];
		used[e]=1;
		if(e&1) used[e+1]=1;
		else used[e-1]=1;
		if(wi[e]==1 && d[p]%ERA==1)
		{
			wi[e]=(ll)L-d[t]/ERA-d[t]%ERA+1;
			if(e&1) wi[e+1]=wi[e];
			else wi[e-1]=wi[e];
		}
	}
	printf("YES\n");
	for(int i=2;i<=egtot;i+=2)
	{
		printf("%I64d %I64d ",eg[i]-1,es[i]-1);
		if(wi[i]>=ERA)
			printf("%I64d\n",wi[i]/ERA);
		else if(used[i]==1)
			printf("%I64d\n",wi[i]);
		else printf("%I64d\n",INF);
	}
/*	std::sort(se+1,se+1+ss,cmp);
	bool flag=0;
	for(int i=1;i<=ss;i++)
	{
		if(flag==1)
		{prt[se[i].id].w=1;continue;}
		if(dis1[se[i].p1]>dis1[se[i].p2])
			std::swap(se[i].p1,se[i].p2);
		int p1=se[i].p1,p2=se[i].p2,id=se[i].id;
		if(dis2[p2]<ERA)
		{
			if(dis1[p1]+dis2[p2]<L)
			{
				printf("YES\n");
				flag=1;
				prt[id].w=L-dis1[p1]-dis2[p2];
			}
			else
			{
				setone(p1,p2);
				prt[id].w=1;
			}
		}
		else
		{
			setone(p1,p2);
			prt[id].w=1;
		}
	}
	if(!flag) return 0;
		*/
}
/*
5 6 99 0 4
0 1 10
1 2 30
2 3 20
3 4 40
0 2 0
2 4 0
*/