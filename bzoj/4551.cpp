#include <cstdio>
#define N 100050
int le[N],ri[N],h[N];
int val[N*4];
int timetip;
int eg[N*2],nxt[N*2],head[N],egtot;
void setTree(int p,int fa)
{
	h[p]=h[fa]+1;
	le[p]=++timetip;
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa)
			setTree(eg[i],p);
	ri[p]=timetip;
}
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
inline void pushdown(int p){if(h[val[p*2]]<h[val[p]]) val[p*2]=val[p];if(val[p*2+1]<h[val[p]]) val[p*2+1]=val[p];}
void add(int p,int l,int r,int gl,int gr,int v)
{
	if(gl==l && gr==r)
	{
		if(h[v]>val[p]) val[p]=v;
		if(l!=r) pushdown(p);
		return;
	}
	pushdown(p);
	int mid=(l+r)/2;
	if(gr<=mid) add(p*2,l,mid,gl,gr,v);
	else if(gl>mid) add(p*2+1,mid+1,r,gl,gr,v);
	else add(p*2,l,mid,gl,mid,v),add(p*2+1,mid+1,r,mid+1,gr,v);
}
int query(int p,int l,int r,int gp)
{
	if(l==r && l==gp)
		return val[p];
	pushdown(p);
	int mid=(l+r)/2;
	if(gp<=mid) return query(p*2,l,mid,gp);
	else return query(p*2+1,mid+1,r,gp);
}
int main()
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	setTree(1,0);
	add(1,1,n,le[1],ri[1],1);
	char s[3];
	for(int p;Q;Q--)
	{
		scanf("%s%d",s,&p);
		if(s[0]=='Q')
			printf("%d\n",query(1,1,n,le[p]));
		else
			add(1,1,n,le[p],ri[p],p);
	}
}
