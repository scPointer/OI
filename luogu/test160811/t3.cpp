#include <cstdio>
#include <algorithm>
#define N 100005
#define ls p<<1
#define rs (p<<1)+1
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define INF 1000000
//#define dbg(x) printf("%s=%d\n",#x,x)
int eg[N*2],nxt[N*2],head[N],egtot;
int h[N],sz[N],fson[N],fa[N];
int top[N],pos[N],fp[N],timetip;
int n;
int gfa[N][18];

int prev[N*5],val[N*5];
struct Query{int a,b,len,lca,id;}qe[N];
bool cmp(Query a,Query b){return a.len<b.len;}
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
void setTree(int p)
{
	sz[p]=1;
	h[p]=h[fa[p]]+1;
	gfa[p][0]=fa[p];
	for(int i=1;gfa[p][i-1]!=0;i++)
		gfa[p][i]=gfa[gfa[p][i-1]][i-1];
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa[p])
		{
			fa[eg[i]]=p;
			setTree(eg[i]);
			sz[p]+=sz[eg[i]];
			if(sz[eg[i]]>sz[fson[p]]) fson[p]=eg[i];
		}
}
void dfs2(int p,int tp)
{
	++timetip;
	pos[p]=timetip;fp[timetip]=p;
	top[p]=tp;
	if(fson[p]) dfs2(fson[p],tp);
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa[p] && eg[i]!=fson[p])
			dfs2(eg[i],eg[i]);
}
int getLca(int p1,int p2)
{
	if(p1==p2) return p1;
	if(h[p1]<h[p2]) std::swap(p1,p2);
	for(int i=17;i>=0;i--)
		if(h[p1]-h[p2]>=(1<<i))
			p1=gfa[p1][i];
	if(p1==p2) return p1;
	for(int i=17;i>=0;i--)
		if(gfa[p1][i]!=gfa[p2][i])
			p1=gfa[p1][i],p2=gfa[p2][i];
	return fa[p1];
}
inline void pushdown(int p)
{
	if(prev[p])
	{
		val[p]+=prev[p];
		prev[ls]+=prev[p];
		prev[rs]+=prev[p];
		prev[p]=0;
	}
}
inline void update(int p){val[p]=Max(val[ls]+prev[ls],val[rs]+prev[rs]);}
void addTree(int p,int l,int r,int gl,int gr,int v)
{
	if(l!=r) pushdown(p);
	if(l==gl && r==gr)
	{
		if(l==r)
		{
			val[p]+=prev[p]+v;
			prev[p]=0;
		}
		else
		{
			prev[p]+=v;
			pushdown(p);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(gr<=mid) addTree(ls,l,mid,gl,gr,v);
	else if(gl>mid) addTree(rs,mid+1,r,gl,gr,v);
	else addTree(ls,l,mid,gl,mid,v),addTree(rs,mid+1,r,mid+1,gr,v);
	update(p);
}
void add(int p1,int p2,int v)
{
//	dbg(p1);dbg(p2);printf("LLLLLL\n");
	while(top[p1]!=top[p2])
	{
		if(h[top[p1]]<h[top[p2]]) std::swap(p1,p2);
//		dbg(p1);dbg(pos[p1]);
		addTree(1,1,n,pos[top[p1]],pos[p1],v);
		p1=fa[top[p1]];
	}
	if(h[p1]<h[p2]) std::swap(p1,p2);
//	dbg(p1);dbg(p2);
	addTree(1,1,n,pos[p2],pos[p1],v);
}
int main()
{
//	freopen("t3.in","r",stdin);
	int m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);addEdge(p2,p1);
	}
	setTree(1);
	dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&qe[i].a,&qe[i].b);
		qe[i].lca=getLca(qe[i].a,qe[i].b);
		qe[i].len=h[qe[i].a]+h[qe[i].b]+1-h[qe[i].lca]*2;
		qe[i].id=i;
	}
	std::sort(qe+1,qe+1+m,cmp);
	int p1=1,p2=0,ans=INF;
	while(p2<m)
	{
		while(p2<m && val[1]<k)
		{
			++p2;
			add(qe[p2].a,qe[p2].b,1);
		}
		while(p1<=p2 && val[1]>=k)
		{
			ans=Min(qe[p2].len-qe[p1].len,ans);
			add(qe[p1].a,qe[p1].b,-1);
			++p1;
		}
	}
	if(ans==INF) printf("-1");
	else printf("%d",ans);
}
