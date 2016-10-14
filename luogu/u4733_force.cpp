#include <cstdio>
#include <vector>
using namespace std;
#define N 100005
#define NDS (33*N)
#define pb push_back
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int cnt[NDS],ls[NDS],rs[NDS],ccnt;
int query(int rt,int p,int bs=30)
{
	if(bs==-1 || rt==0) return cnt[rt];
	if((p>>bs)&1) return query(rs[rt],p,bs-1);
	else return query(ls[rt],p,bs-1);
}
int add(int rt,int p,int bs=30)
{
	int nrt=++ccnt;
	cnt[nrt]=cnt[rt]+1;
	if(bs==-1) return nrt;
	if((p>>bs)&1)
	{
		ls[nrt]=ls[rt];
		rs[nrt]=add(rs[rt],p,bs-1);
	}
	else
	{
		ls[nrt]=add(ls[rt],p,bs-1);
		rs[nrt]=rs[rt];
	}
	return nrt;
}


int dset[N],sz[N];
int dfind(int p){return dset[p]==p? p:dset[p]=dfind(dset[p]);}
void merge(int p1,int p2){dset[p1]=p2;sz[p2]+=sz[p1];}

struct Edge{int pfr,pto,w;}eg[N<<1];
int nxt[N<<1],head[N],egtot;
void addEdge(int p1,int p2,int w)
{
	eg[++egtot]=(Edge){p1,p2,w};
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}

int fa[N][18],h[N];
int wi[N];
void dfs(int p)
{
	for(int i=head[p];i;i=nxt[i])
	{
		Edge& e=eg[i];
		if(e.pto!=fa[p][0])
		{
			fa[e.pto][0]=p;
			h[e.pto]=h[p]+1;
			wi[e.pto]=wi[p]^e.w;
//			for(int i=1;i<=17;i++)
//				fa[e.pto][i]=fa[fa[e.pto][i-1]][i-1];
			dfs(e.pto);
		}
	}
}
int lca(int a,int b)
{
	if(h[a]<h[b]) swap(a,b);
	int delta=h[a]-h[b];
	for(int i=17;i>=0;i--)
		if((delta>>i)&1) a=fa[a][i];
	if(a==b) return a;
	for(int i=17;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}

int odr[N];
int rot[N];
long long ans[N];
vector<int> st[N];
int main()
{
	freopen("u4733.in","r",stdin);
	int n=RD();
	for(int i=1,p1,p2,w;i<=n-1;i++)
	{
		p1=RD();p2=RD();w=RD();
		addEdge(p1,p2,w);
		addEdge(p2,p1,w);
	}
	for(int i=1;i<=n-1;i++)
		odr[i]=RD();
	for(int i=0;i<=17;i++)
		fa[1][i]=1;
	dfs(1);
	
	rot[0]=add(0,0);
	for(int i=1;i<=n;i++)
		dset[i]=i,sz[i]=1,rot[i]=rot[0],st[i].pb(0);
	for(int i=n-1;i>=1;i--)
	{
		ans[i]=ans[i+1];
		int p1=dfind(eg[odr[i]<<1].pfr);
		int p2=dfind(eg[odr[i]<<1].pto);
		if(sz[p1]>sz[p2]) swap(p1,p2);
/*
		int trs=wi[p1]^wi[p2];
		for(int j=st[p1].size()-1;j>=0;j--)
			st[p1][j]^=trs;
		for(int j=st[p1].size()-1;j>=0;j--)
			for(int k=st[p2].size()-1;k>=0;k--)
				if(st[p1][j]==st[p2][k])
					ans[i]++;
		for(int j=st[p1].size()-1;j>=0;j--)
			st[p2].pb(st[p1][j]);
			*/
		ans[i]+=(long long)sz[p1]*sz[p2];
		merge(p1,p2);
	}
	long long hh=0;
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]),hh^=ans[i];
	printf("hh= %lld\n",hh);
}