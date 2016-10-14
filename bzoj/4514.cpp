#include <cstdio>
#define N 205
#define M 50005
#define LIM 31623
#define INF 1000000005
#define INFD 1000000000000000000ll
#define LEN 1000000
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
int prm[3434],pcnt;
bool notprm[LIM];
int nds,S,T;
int val[N],num[N],wei[N];
struct Edge{
	int pfr,pto,flo,lim;
	long long cst;
	void set(int s,int t,int f,int l,long long c){pfr=s;pto=t;flo=f;lim=l;cst=c;}
}eg[M];
int head[N],nxt[M],egtot;
void getprime()
{
	for(int i=2;i<=LIM;i++)
		if(notprm[i]==0){
			for(int j=i*i;j<=LIM;j+=i)
				notprm[j]=1;
		}
	for(int i=2;i<=LIM;i++)
		if(notprm[i]==0)
			prm[++pcnt]=i;
}
bool isPrime(int p)
{
	for(int i=1;prm[i]*prm[i]<=p;i++)
		if(p%prm[i]==0) return 0;
	return 1;
}
void addEdge(int p1,int p2,int lim,long long cst)
{
	eg[egtot].set(p1,p2,0,lim,-cst);
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
	eg[egtot].set(p2,p1,0,0,cst);
	nxt[egtot]=head[p2];
	head[p2]=egtot++;
}
int sp[LEN],insp[N];
long long dis[N];
int pre[N];
void maxflow()
{
	long long sumcst=0,cst=0;
	int flow=0;
	while(sumcst+cst<=0)
	{
		sumcst+=cst;
		cst=0;
		for(int i=1;i<=nds;i++) dis[i]=INFD,insp[i]=0;
		int l,r,p;sp[l=r=1]=S;insp[S]=1;pre[S]=-1;dis[S]=0;
		while(l<=r)
		{
			p=sp[l++];insp[p]=0;
			for(int i=head[p];i!=-1;i=nxt[i])
			{
				Edge& e=eg[i];
				if(e.flo<e.lim && dis[p]+e.cst<dis[e.pto])
				{
					dis[e.pto]=dis[p]+e.cst;
					pre[e.pto]=i;
					if(insp[e.pto]==0)
					{
						insp[e.pto]=1;
						sp[++r]=e.pto;
					}
				}
			}
		}
		if(dis[T]==INFD) break;
		int f=INF;
		for(p=pre[T];p!=-1;p=pre[eg[p].pfr])
			f=Min(f,eg[p].lim-eg[p].flo);
		for(p=pre[T];p!=-1;p=pre[eg[p].pfr])
			{eg[p].flo+=f;eg[p^1].flo-=f;}
		cst=dis[T]*f;
		if(sumcst+cst>0)
		{
			flow+= (int)((-sumcst)/dis[T]);
			break;
		}
		flow+=f;
		
	}
	printf("%d",flow);
}
int vis[N],q[N];
int lk[N];
void init(int n)
{
	for(int i=1;i<=nds;i++) head[i]=-1;
	for(int i=1,l,r,p,p1,p2;i<=n;i++)
		if(vis[i]==0)
		{
			vis[i]=1;
			q[l=r=1]=i;
			while(l<=r)
			{
				p=q[l++];
				for(int j=1;j<=n;j++)
					if(vis[p]!=vis[j] && j!=lk[p])
					{
						p1=Max(val[p],val[j]);
						p2=val[p]+val[j]-p1;
						if(p1%p2==0 && isPrime(p1/p2))
						{
							vis[p]==1? addEdge(p,j,INF,(long long)wei[p]*wei[j]): addEdge(j,p,INF,(long long)wei[p]*wei[j]);
							if(vis[j]==0) q[++r]=j,vis[j]=-vis[p],lk[j]=p;
						}
					}
			}
		}
	for(int i=1;i<=n;i++)
		if(vis[i]==1) addEdge(S,i,num[i],0);
		else addEdge(i,T,num[i],0);
}
int main()
{
	int n;
	scanf("%d",&n);nds=n+2;S=n+1;T=n+2;
	getprime();
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	for(int i=1;i<=n;i++) scanf("%d",&wei[i]);
	init(n);
	maxflow();
}
