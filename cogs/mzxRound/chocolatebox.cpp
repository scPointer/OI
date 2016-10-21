#include <cstdio>
#include <cmath>
#include <ctime>
#define N 1000005
typedef long long ll;
int n,m,k,p1,p2;
int phip2;
int getphi(int p)
{
	int lim=(int)(sqrt(p))+5;
	int res=p;
	for(int i=2;i<=lim && i<p;i++)
		if(p%i==0)
		{
			res=(ll)res*(i-1)/i;
			while(p%i==0)
				p/=i;
		}
	if(p>1)
		res=(ll)res*(p-1)/p;
	return res;
}
int fpower(int a,int b,int mo)
{
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%mo)
		if(b&1)
			res=(ll)res*a%mo;
	return res;
}

#define ls p<<1
#define rs (p<<1)|1
int a[N];
int val1[N*5],val2[N*5];
void build(int p,int l=1,int r=n)
{
	if(l==r)
	{
		val1[p]=a[l]%p1;
		val2[p]=a[l]%phip2;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	val1[p]=(ll)val1[ls]*val1[rs]%p1;
	val2[p]=(ll)val2[ls]*val2[rs]%phip2;
}
int query1(int p,int l,int r,int gl,int gr)
{
	if(l==gl && r==gr)
		return val1[p];
	int mid=(l+r)>>1;
	if(gr<=mid) return query1(ls,l,mid,gl,gr);
	else if(gl>mid) return query1(rs,mid+1,r,gl,gr);
	else return ((ll)query1(ls,l,mid,gl,mid))*query1(rs,mid+1,r,mid+1,gr)%p1;
}
int query2(int p,int l,int r,int gl,int gr)
{
	if(l==gl && r==gr)
		return val2[p];
	int mid=(l+r)>>1;
	if(gr<=mid) return query2(ls,l,mid,gl,gr);
	else if(gl>mid) return query2(rs,mid+1,r,gl,gr);
	else return ((ll)query2(ls,l,mid,gl,mid))*query2(rs,mid+1,r,mid+1,gr)%phip2;
}
int main()
{
	int c1=clock();
	freopen("chocolatebox.in","r",stdin);
//	freopen("chocolatebox.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&k,&p1,&p2);
	phip2= p2>0? getphi(p2): 1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	printf("time %d\n",clock()-c1);
	for(int i=1;i<=m;i++)
	{
		int tp,l,r;scanf("%d%d%d",&tp,&l,&r);
		if(tp==1)
			printf("%d\n",query1(1,1,n,l,r));
		else
			printf("%d\n",fpower(k,query2(1,1,n,l,r),p2));
	}
	printf("time %d\n",clock()-c1);
}
