#include <cstdio>
#define N 200005
#define ND 1200005
#define Swap(a,b) {_temp=a;a=b;b=_temp;}
int son[N][2],fa[N];
bool rev[N];
int idx[N],minx[N];
int stk[N];
int _temp;
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return son[fa[p]][0]!=p && son[fa[p]][1]!=p;}
inline void sets(int d,int p,int f){son[f][d]=p;fa[p]=f;}
inline void update(int p)
{
	static int lson,rson;
	lson=son[p][0];rson=son[p][1];
	minx[p]=p;//!!
	if(idx[minx[lson]]<idx[minx[p]])
		minx[p]=minx[lson];
	if(idx[minx[rson]]<idx[minx[p]])
		minx[p]=minx[rson];
}
inline void pushdown(int p)
{
	if(rev[p])
	{
		Swap(son[p][0],son[p][1])
		if(son[p][0]!=0) rev[son[p][0]]^=1;
		if(son[p][1]!=0) rev[son[p][1]]^=1;
		rev[p]=0;
	}
}
void rotate(int p)
{
	static int d,Fa;
	d=getd(p);Fa=fa[p];
	isrt(Fa)? (void)(fa[p]=fa[Fa]): sets(getd(Fa),p,fa[Fa]);
	sets(d,son[p][d^1],Fa);
	sets(d^1,Fa,p);
	update(Fa);
}
void splay(int p)
{
	static int top,pt;
	top=0;
	for(pt=p;!isrt(pt);pt=fa[pt]) stk[++top]=pt;
	stk[++top]=pt;
	for(pt=top;pt>=1;pt--) pushdown(stk[pt]);
	while(!isrt(p))
	{
		if(!isrt(fa[p]))
			getd(p)==getd(fa[p])?rotate(fa[p]):rotate(p);
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
		son[p][1]=y;
		y=p;
		p=fa[p];
	}
	return y;
}
void mkroot(int p)
{
	int res=access(p);
	rev[res]^=1;
	splay(p);
}
void link(int x,int y)
{
	mkroot(x);
	fa[x]=y;
	access(x);
}
void split(int x,int y)
{
	mkroot(x);
	access(y);
	splay(y);
}
void cut(int x,int y)
{
	split(x,y);
	fa[x]=0;
	son[y][getd(x)]=0;
}
int solve(int x,int y)
{
	mkroot(x);
	access(y);
	splay(y);
	int preEdge=idx[minx[y]];
	//unfinished...
}
int ls[ND],rs[ND],ct[ND],rot[N],ndcnt;
int ntr[N];
int n;
int setTree(int l,int r)
{
	int newnd=++ndcnt;
	if(l==r) return newnd;
	ls[newnd]=setTree(l,(l+r)/2);
	rs[newnd]=setTree((l+r)/2+1,r);
	return newnd;
}
int upd_pre(int prt,int p,int nb)
{
	int nrt=++ndcnt,l=1,r=n+1,mid;ct[nrt]=ct[prt]+nb;
	int setrt=nrt;
	while(l<r)
	{
		mid=(l+r)/2;
		if(p<=mid)
		{
			rs[nrt]=rs[prt];ls[nrt]=++ndcnt;
			nrt=ls[nrt];prt=ls[prt];
			r=mid;
		}
		else
		{
			ls[nrt]=ls[prt];rs[nrt]=++ndcnt;
			nrt=rs[nrt];prt=rs[prt];
		}
		ct[nrt]=ct[prt]+nb;
	}
	return setrt;
}
int query(int lt,int rt,int p)
{
	int ll=1,rr=n+1,mid,res=0;
	while(ll<rr)
	{
		mid=(ll+rr)/2;
		if(p<=mid) rr=mid,lt=ls[lt],rt=ls[rt];
		else
		{
			ll=mid+1;
			res+=ct[ls[rt]]-ct[ls[lt]];
			lt=rs[lt];rt=rs[rt];
		}
	}
	res-=ct[rt]-ct[lt];
	return res;
}
void setPreTree()
{
	rot[0]=setTree(1,n+1);
	for(int i=1;i<=n;i++)
		rot[i]=upd_pre(rot[i-1],ntr[i],1);
}

int dset[N];
inline int find(int p){return dset[p]==p?p:dset[p]=find(p);}
int main()
{
	int m,k,tp;
	scanf("%d%d%d%d",&n,&m,&k,&tp);
	
	
}
