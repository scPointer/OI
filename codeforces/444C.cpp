#include <cstdio>
#define N 400005
#define ls p<<1
#define rs (p<<1)+1
#define mabs(x) ((x)>0?(x):-(x))
typedef long long ll;
ll ans[N];
ll prv[N];
int col[N];
int prc[N];
void update(int p,int l,int r)
{
	if(col[ls]!=0 && col[rs]==col[ls])
		col[p]=col[ls];
	else col[p]=0;
	int mid=(l+r)>>1;
	ans[p]=ans[ls]+prv[ls]*(mid-l+1)+ans[rs]+prv[rs]*(r-mid);
}
void pushdown(int p,int l,int r)
{
	if(l==r)
	{
		ans[p]+=prv[p];
		prv[p]=0;
		if(prc[p]){col[p]=prc[p];prc[p]=0;}
		return;
	}
	if(prc[p])
	{
		col[p]=col[ls]=col[rs]=prc[ls]=prc[rs]=prc[p];
		prc[p]=0;
	}
	if(prv[p])
	{
		ans[p]+=prv[p]*(r-l+1);
		prv[ls]+=prv[p];
		prv[rs]+=prv[p];
		prv[p]=0;
	}
	update(p,l,r);
}
ll query(int p,int l,int r,int gl,int gr)
{
	pushdown(p,l,r);
	if(l==gl && r==gr)
		return ans[p];
	int mid=(l+r)>>1;
	if(gr<=mid) return query(ls,l,mid,gl,gr);
	else if(gl>mid) return query(rs,mid+1,r,gl,gr);
	else return query(ls,l,mid,gl,mid)+query(rs,mid+1,r,mid+1,gr);
}
void chg(int p,int l,int r,int c)
{
	pushdown(p,l,r);
	if(col[p]!=0)
	{
		prv[p]+=mabs(col[p]-c);
		prc[p]=c;
		pushdown(p,l,r);
	}
	else
	{
		int mid=(l+r)>>1;
		chg(ls,l,mid,c);
		chg(rs,mid+1,r,c);
		update(p,l,r);
	}
}
void merge(int p,int l,int r,int gl,int gr,int c)
{
	pushdown(p,l,r);
	if(l==gl && r==gr)
		chg(p,l,r,c);
	else
	{
		int mid=(l+r)>>1;
		if(gr<=mid) merge(ls,l,mid,gl,gr,c);
		else if(gl>mid) merge(rs,mid+1,r,gl,gr,c);
		else merge(ls,l,mid,gl,mid,c),merge(rs,mid+1,r,mid+1,gr,c);
		update(p,l,r);
	}
}
void init(int p,int l,int r)
{
	if(l==r)
		col[p]=l;
	else
	{
		int mid=(l+r)>>1;
		init(ls,l,mid);
		init(rs,mid+1,r);
		update(p,l,r);
	}
}
int main()
{
	int n,m;scanf("%d%d'",&n,&m);
	init(1,1,n);
	while(m--)
	{
		int tp;scanf("%d",&tp);
		if(tp==1)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			merge(1,1,n,l,r,x);
		}
		else
		{
			int l,r;scanf("%d%d",&l,&r);
			printf("%I64d\n",query(1,1,n,l,r));
		}
	}
}
