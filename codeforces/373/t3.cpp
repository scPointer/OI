#include <cstdio>
#define N 800005
#define mo 1000000007
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define ls p<<1
#define rs (p<<1)+1
typedef long long ll;
int n,m;
struct Matrix{
	ll a[2][2];
}mt[205];
Matrix mult(Matrix x,Matrix y)
{
	Matrix c;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			c.a[i][j]=0;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				c.a[i][j]=((ll)c.a[i][j]+(ll)x.a[i][k]*y.a[k][j])%mo;
	return c;
}
void init(ll lim)
{
	mt[0].a[0][0]=0;
	mt[0].a[0][1]=1;
	mt[0].a[1][0]=1;
	mt[0].a[1][1]=1;
	ll t=2;
	for(int i=1;t<=lim;i++,t<<=1)
	{
		mt[i]=mult(mt[i-1],mt[i-1]);
	}
}
Matrix calc(ll b)
{
	Matrix res;
	res.a[0][0]=1;
	res.a[0][1]=0;
	res.a[1][0]=0;
	res.a[1][1]=1;
	for(int i=0;b;i++)
	{
		if(b&1) res=mult(res,mt[i]);
		b>>=1;
	}
	return res;
}
ll a1[N],a2[N],sum[N];
Matrix prev[N];
void update(int p)
{
	a1[p]=(a1[ls]*prev[ls].a[0][0]+a2[ls]*prev[ls].a[0][1]+a1[rs]*prev[rs].a[0][0]+a2[rs]*prev[rs].a[0][1])%mo;
	a2[p]=(a1[ls]*prev[ls].a[1][0]+a2[ls]*prev[ls].a[1][1]+a1[rs]*prev[rs].a[1][0]+a2[rs]*prev[rs].a[1][1])%mo;
}
void pushdown(int p)
{
	prev[ls]=mult(prev[ls],prev[p]);
	prev[rs]=mult(prev[rs],prev[p]);
	prev[p].a[0][0]=1;
	prev[p].a[0][1]=0;
	prev[p].a[1][0]=0;
	prev[p].a[1][1]=1;
	update(p);
}
void merge(int p,int l,int r,int gl,int gr,Matrix val)
{
	if(l==gl && r==gr)
	{
		if(l==r)
		{
			prev[p]=mult(prev[p],val);
		}
		else
		{
			prev[p]=mult(prev[p],val);
			pushdown(p);
		}
		return;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(gr<=mid) merge(ls,l,mid,gl,gr,val);
	else if(gl>mid) merge(rs,mid+1,r,gl,gr,val);
	else merge(ls,l,mid,gl,mid,val),merge(rs,mid+1,r,mid+1,gr,val);
	update(p);
}
ll query(int p,int l,int r,int gl,int gr)
{
	if(l!=r) {pushdown(p);}
	if(l==gl && r==gr)
	{
		return (a1[p]*prev[p].a[0][0]+a2[p]*prev[p].a[0][1])%mo;
	}
	int mid=(l+r)>>1;
	if(gr<=mid) return query(ls,l,mid,gl,gr);
	else if(gl>mid) return query(rs,mid+1,r,gl,gr);
	else return (query(ls,l,mid,gl,mid)+query(rs,mid+1,r,mid+1,gr))%mo;
	update(p);
}
int it[N];
void build(int p,int l,int r)
{
	prev[p].a[0][0]=1;
	prev[p].a[0][1]=0;
	prev[p].a[1][0]=0;
	prev[p].a[1][1]=1;
	if(l==r)
	{
		if(it[l]==1) a1[p]=a2[p]=1;
		else
		{
			Matrix r=calc(it[l]-1);
			a1[p]=(r.a[0][0]+r.a[0][1])%mo;
			a2[p]=(r.a[1][0]+r.a[1][1])%mo;
		}
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);

	update(p);
}

int main()
{
	scanf("%d%d",&n,&m);
	init(10000000000000000ll);
	for(int i=1;i<=n;i++)
		scanf("%d",&it[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int tp;scanf("%d",&tp);
		if(tp==1)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			merge(1,1,n,l,r,calc(x));
		}
		else
		{
			int l,r;scanf("%d%d",&l,&r);
			printf("%I64d\n",query(1,1,n,l,r)%mo);
		}
	}
}
