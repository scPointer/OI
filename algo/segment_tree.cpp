#include <cstdio>
#define N 205*4
#define ls (p<<1)
#define rs (p<<1)|1
#define Min(a,b) (a<b?a:b)
int mn[N],prev[N];
int n;
void update(int p)
{
	mn[p]=Min(mn[ls],mn[rs]);
}
void pushdown(int p)
{
	if(prev[p])
	{
		prev[ls]+=prev[p];
		prev[rs]+=prev[p];
		mn[ls]+=prev[p];
		mn[rs]+=prev[p];
		prev[p]=0;
	}
}
void modify(int gl,int gr,int val,int p=1,int l=1,int r=n)
{
	if(l!=r) pushdown(p);
	if(gl==l && gr==r)
	{
		mn[p]+=val;
		prev[p]+=val;
		return;
	}
	int mid=(l+r)>>1;
	if(gr<=mid) modify(gl,gr,val,ls,l,mid);
	else if(gl>mid) modify(gl,gr,val,rs,mid+1,r);
	else modify(gl,mid,val,ls,l,mid),modify(mid+1,gr,val,rs,mid+1,r);
	update(p);
}
int query(int gl,int gr,int p=1,int l=1,int r=n)
{
	if(l!=r) pushdown(p);
	if(gl==l && gr==r)
	{
		return mn[p];
	}
	int mid=(l+r)>>1;
	if(gr<=mid) return query(gl,gr,ls,l,mid);
	else if(gl>mid) return query(gl,gr,rs,mid+1,r);
	else
	{
		int a1=query(gl,mid,ls,l,mid);
		int a2=query(mid+1,gr,rs,mid+1,r);
		return Min(a1,a2);
	}
}
int main()
{
	int T;scanf("%d%d",&n,&T);
	while(T--)
	{
		int tp;scanf("%d",&tp);
		if(tp==1)
		{
			int l,r,val;scanf("%d%d%d",&l,&r,&val);
			modify(l,r,val);
		}
		else
		{
			int l,r;scanf("%d%d",&l,&r);
			int ans=query(l,r);
			printf("%d\n",ans);
		}
	}
}