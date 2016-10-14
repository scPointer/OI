#include <cstdio>
#define N 300005
#define INF 1000000000
#define Max(a,b) (a>b?a:b)
int fa[N],son[N][2];
bool rev[N];
int sum[N],dmax[N],val[N];
int ndcnt;
int stk[N],tops;
inline void sets(int d,int p,int f){son[f][d]=p;fa[p]=f;}
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return son[fa[p]][0]!=p && son[fa[p]][1]!=p;}
inline void pushdown(int p)
{
	if(rev[p])
	{
		son[p][0]^=son[p][1]^=son[p][0]^=son[p][1];
		if(son[p][0]!=0) rev[son[p][0]]^=1;
		if(son[p][1]!=0) rev[son[p][1]]^=1;
		rev[p]=0;
	}
}
inline void update(int p)
{
	int ls=son[p][0],rs=son[p][1];
	sum[p]=val[p]+sum[ls]+sum[rs];
	dmax[p]=val[p];
	if(dmax[ls]>dmax[p]) dmax[p]=dmax[ls];
	if(dmax[rs]>dmax[p]) dmax[p]=dmax[rs];
}
void rotate(int p)
{
	int d=getd(p),Fa=fa[p];
	isrt(Fa)? (void)(fa[p]=fa[Fa]): sets(getd(Fa),p,fa[Fa]);
	sets(d,son[p][d^1],Fa);
	sets(d^1,Fa,p);
	update(Fa);
}
void splay(int p)
{
	int pt;tops=0;
	for(pt=p;!isrt(pt);pt=fa[pt]) stk[++tops]=pt;
	stk[++tops]=pt;
	for(pt=tops;pt>0;pt--) pushdown(stk[pt]);
	while(!isrt(p))
	{
		if(!isrt(fa[p]))
			getd(p)==getd(fa[p])? rotate(fa[p]): rotate(p);
		rotate(p);
	}
	update(p);
}
int access(int p)
{
	int y=0;
	while(p!=0)
	{
		splay(p);
		son[p][1]=y;y=p;p=fa[p];
	}
	return y;
}
void mkroot(int p)
{
	int pt=access(p);
	rev[pt]=1;
	splay(p);
}
void link(int p,int pt)
{
	mkroot(p);
	fa[p]=pt;
//	access(p);
}
int eg[N*2],nxt[N*2],head[N],egtot;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
void setTree(int p)
{
	for(int i=head[p],pt;i;i=nxt[i])
		if(eg[i]!=fa[p])
		{
			pt=eg[i];
			fa[pt]=p;
			setTree(pt);
		}
}
int main()
{
	freopen("1036.in","r",stdin);
	freopen("1036.out","w",stdout);
	int n,m;dmax[0]=-INF;
	scanf("%d",&n);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	setTree(1);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1;i<=n;i++) access(i);
	scanf("%d",&m);
	char odr[11];
	for(int i=1,p1,p2;i<=m;i++)
	{
		scanf("%s%d%d",odr,&p1,&p2);
		if(odr[1]=='H')
			val[p1]=p2;
		else if(odr[1]=='M')
		{
			mkroot(p1);
			access(p2);
			splay(p2);
			printf("%d\n",Max(dmax[son[p2][0]],val[p2]));
		}
		else
		{
			mkroot(p1);
			access(p2);
			splay(p2);
			printf("%d\n",sum[son[p2][0]]+val[p2]);
		}
	}
	
}
