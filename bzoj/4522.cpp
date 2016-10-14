#include <cstdio>
#include <cstdlib>
typedef long long ll;
void exgcd(ll a,ll b,ll& x,ll& y)
{
	if(b==0){x=1;y=0;}
	else
	{
		exgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}
}
ll gcd(ll a,ll b){return b==0? a:gcd(b,a%b);}
ll fastmult(ll a,ll b,ll mo)
{
	a%=mo;b%=mo;
	ll res=0;
	while(b)
	{
		if(b&1) res=(res+a)%mo;
		a=(a+a)%mo;
		b>>=1;
	}
	return res;
}
ll fastpower(ll c,ll pow,ll mo)
{
	c%=mo;
	ll res=1;
	while(pow)
	{
		if(pow&1) res=fastmult(res,c,mo);
		c=fastmult(c,c,mo);
		pow>>=1;
	}
	return res;
}
ll div(ll N)//pollard_pho
{
	ll c=rand()%(N-1)+1;
	ll xa,xb;xa=xb=rand()%(N-1)+1;
	int ta=1,tb=2;
	while(1)
	{
		++ta;
		if(xa<=0 || xb<=0) printf("ERR");
		xa=(fastmult(xa,xa,N)+c)%N;
		ll d=gcd(N,((xa-xb)+N)%N);
		if(d>1 && d!=N) return d;
		if(xa==xb) return N;
		if(ta==tb)
		{
			tb=tb+tb;xb=xa;
//			printf("%d\n",tb);
		}
	}
}
int main()
{
	srand(3997);
	ll e,N,c;
	scanf("%lld%lld%lld",&e,&N,&c);
	ll p; while((p=div(N))==N);
	ll q=N/p;
	ll r=(p-1)*(q-1);
	ll d,y; exgcd(e,r,d,y);
	d=(d%r+r)%r;
	ll n=fastpower(c,d,N);
	printf("%lld %lld\n",d,n);
}