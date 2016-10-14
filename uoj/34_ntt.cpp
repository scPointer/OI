#include <cstdio>
#define Swap(a,b) {_t=a;a=b;b=_t;}
#define N 262155
#define mo 2281701377ll//17*2^27+1
#define primitive_root 3
inline int RD()
{
	static int res;
	static char cr;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
long long _t;
long long a[N],b[N],wi[N],trb;
int rev[N];
int n,m,bts,ep;
long long fastpower(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1) res=(res*a)%mo;
		a=(a*a)%mo;
		b>>=1;
	}
	return res;
}
void transform(long long* c,int t)
{
	for(int i=2;i<=bts;i<<=1)
	{
		int l=bts/i;
		int h=i>>1;
		for(int j=0;j<bts;j+=i)
		{
			for(int k=0;k<h;k++)
			{
				long long w=(c[j+h+k]*wi[(l*k*t+bts)%bts])%mo;
				c[j+h+k]=(c[j+k]-w+mo)%mo;
				c[j+k]=(c[j+k]+w+mo)%mo;
			}
		}
	}
}
int main()
{
	n=RD();m=RD();
	bts=1;while(bts<=n+m) bts<<=1,ep++;
	trb=fastpower(bts,mo-2);
	
	for(int i=1;i<bts;i++) rev[i]=(rev[i>>1]>>1) | (i&1)<<(ep-1);
	
	wi[0]=1;wi[1]=fastpower(fastpower(primitive_root,17),1<<(27-ep));
	for(int i=1;i<=bts;i++)	wi[i]=(wi[i-1]*wi[1])%mo;
	for(int i=0;i<=n;i++) a[rev[i]]=RD();
	for(int i=0;i<=m;i++) b[rev[i]]=RD();
	transform(a,1);
	transform(b,1);
	for(int i=0;i<bts;i++)
		a[i]=(a[i]*b[i])%mo;
	for(int i=0;i<bts;i++)
		if(rev[i]<i) Swap(a[i],a[rev[i]]);
	transform(a,-1);
	for(int i=0;i<bts;i++) a[i]=(a[i]*trb)%mo;
	for(int i=0;i<=n+m;i++) printf("%lld ",a[i]);
}