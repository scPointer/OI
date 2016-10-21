#include <cstdio>
#include <cmath>
#define N 1000005
typedef long long ll;
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
inline void PRD(int p)
{
	if(!p) return;
	PRD(p/10);
	putc(p%10+'0',stdout);
}
inline void PD(int p)
{
	p? PRD(p):(void)putc('0',stdout);
	putc('\n',stdout);
}

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
#define init(p) (s1[flo][p]=a[p]%p1,s2[flo][p]=a[p]%phip2)
int a[N];
int s1[22][N],s2[22][N];
void build(int flo,int l=1,int r=n)
{
	if(l==r)
	{
		init(l);
		return;
	}
	int mid=(l+r)>>1;
	init(mid);
	for(int i=mid-1;i>=l;i--)
	{
		s1[flo][i]=(ll)s1[flo][i+1]*a[i]%p1;
		s2[flo][i]=(ll)s2[flo][i+1]*a[i]%phip2;
	}
	init(mid+1);
	for(int i=mid+2;i<=r;i++)
	{
		s1[flo][i]=(ll)s1[flo][i-1]*a[i]%p1;
		s2[flo][i]=(ll)s2[flo][i-1]*a[i]%phip2;
	}
	build(flo+1,l,mid);
	build(flo+1,mid+1,r);
}
inline int query(int gl,int gr,int s[][N],int mo)
{
	int flo=0,l=1,r=n,mid;
	if(gl==gr) return a[gl]%mo;
	while(1)
	{
		mid=(l+r)>>1;
		if(gr<=mid)
			r=mid,++flo;
		else if(gl>mid)
			l=mid+1,++flo;
		else
			return (ll)s[flo][gl]*s[flo][gr]%mo;
	}
}
int main()
{
	freopen("chocolatebox.in","r",stdin);
	freopen("chocolatebox.out","w",stdout);
	n=RD();m=RD();k=RD();p1=RD();p2=RD();
	phip2= p2>0? getphi(p2): 1;
	if(p1==0) p1=1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(0,1,n);
	for(int i=1;i<=m;i++)
	{
		int tp,l,r;tp=RD();l=RD();r=RD();
		if(tp==1)
			PD(query(l,r,s1,p1));
		else
			PD(fpower(k,query(l,r,s2,phip2),p2));
	}
}
