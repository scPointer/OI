#include <cstdio>
#include <algorithm>
#define N 100005
#define M 400005
#define ND 4000005
struct Que{int tp,v1,v2;}que[M];
int qcnt;
struct imp{int id,val;}nd[N];
int pos[N],val[N];
int dset[N*2],lson[N*2],rson[N*2],pla[N],setcnt;
bool vis[N*2];
int line[N],lcnt;
int ls[ND],rs[ND],c[ND],rot[N],tcnt;
int n;
bool cmp(imp a,imp b){return a.val<b.val;}
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
void getHash()
{
	for(int i=1,v;i<=n;i++)
	{
		scanf("%d",&v);
		nd[i]=(imp){i,v};
	}
	std::sort(nd+1,nd+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		val[nd[i].id]=i;
		pos[i]=nd[i].id;
	}
}
void getSet(int n)
{
	setcnt=n;
	for(int i=1;i<=n*2;i++) dset[i]=i;
	for(int i=1,tp,p1,p2,f1,f2;i<=qcnt;i++)
	{
		tp=que[i].tp;p1=que[i].v1;p2=que[i].v2;
		if(tp==0)
		{
			f1=find(p1);f2=find(p2);
			if(f1!=f2)
			{
				dset[f1]=dset[f2]=++setcnt;
				lson[setcnt]=f1;
				rson[setcnt]=f2;
			}
		}
	}
}
void setTree(int p)
{
	vis[p]=1;
	if(p<=n){line[++lcnt]=p;pla[p]=lcnt;}
	else
	{
		setTree(lson[p]);
		setTree(rson[p]);
	}
}
int setSegTree(int l,int r)
{
	int newnd=++tcnt;
	if(l==r) return newnd;
	ls[newnd]=setSegTree(l,(l+r)/2);
	rs[newnd]=setSegTree((l+r)/2+1,r);
	return newnd;
}
int update(int prt,int p,int nb)
{
	int nrt=++tcnt,l=1,r=n,mid; c[nrt]=c[prt]+nb;
	int setrt=nrt;
	while(l<r)
	{
		mid=(l+r)/2;
		if(p<=mid)
		{
			ls[nrt]=++tcnt;rs[nrt]=rs[prt];
			nrt=ls[nrt];prt=ls[prt];
			r=mid;
		}
		else
		{
			ls[nrt]=ls[prt];rs[nrt]=++tcnt;
			nrt=rs[nrt];prt=rs[prt];
			l=mid+1;
		}
		c[nrt]=c[prt]+nb;
	}
	return setrt;
}
int query(int lt,int rt,int kth)
{
	if(kth>c[rt]-c[lt]) return -1;
	int l=1,r=n,mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(c[ls[rt]]-c[ls[lt]]>=kth)
			rt=ls[rt],lt=ls[lt],r=mid;
		else
		{
			kth-=c[ls[rt]]-c[ls[lt]];
			rt=rs[rt];lt=rs[lt];l=mid+1;
		}
	}
	return pos[l];
}
int main()
{
	int m,Q;
	scanf("%d%d",&n,&m);
	getHash();
	for(int i=1,p1,p2;i<=m;i++)
	{
		scanf("%d%d",&p1,&p2);
		que[++qcnt]=(Que){0,p1,p2};
	}
	scanf("%d",&Q);
	char rd[5];
	for(int i=1,tp,p1,p2;i<=Q;i++)
	{
		scanf("%s%d%d",rd,&p1,&p2);
		tp= rd[0]=='B'? 0:1;
		que[++qcnt]=(Que){tp,p1,p2};
	}
	getSet(n);
	for(int i=setcnt;i>=1;i--)
		if(vis[i]==0)
			setTree(i);
	for(int i=1;i<=setcnt;i++)
		if(i<=n) lson[i]=rson[i]=pla[i];
		else lson[i]=lson[lson[i]],rson[i]=rson[rson[i]];
		
	rot[0]=setSegTree(1,n);
	for(int i=1;i<=n;i++)
		rot[i]=update(rot[i-1],val[line[i]],1);
	
	for(int i=1;i<=setcnt;i++) dset[i]=i;
	int nscnt=n;
	for(int i=1,tp,v1,v2,f1,f2;i<=qcnt;i++)
	{
		tp=que[i].tp;v1=que[i].v1;v2=que[i].v2;
		if(tp==0)
		{
			f1=find(v1);f2=find(v2);
			dset[f1]=dset[f2]=++nscnt;
		}
		else
		{
			f1=lson[find(v1)]-1;f2=rson[find(v1)];
			printf("%d\n",query(rot[f1],rot[f2],v2));
		}
	}
}
