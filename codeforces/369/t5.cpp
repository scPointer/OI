#include <cstdio>
#include <iostream>
#define mo 1000003
typedef long long ll;
ll fpw(ll a,ll b)
{
	ll res=1;a%=mo;
	while(b)
	{
		if(b&1) res=res*a%mo;
		a=a*a%mo;
		b>>=1;
	}
	return res;
}
int main()
{
	ll n,k;std::cin>>n>>k;
	ll h2=n,setk=k-1;
	while(setk>>=1)
	{
		h2+=setk;
	}
	if(n<=60 && fpw(2,n)-k<0)
	{
		std::cout<<"1"<<' '<<"1";
		return 0;
	}
	else if(k==1)
	{
		std::cout<<"0"<<' '<<"1";
	}

	ll fm=fpw(fpw(2,n),k)*fpw(fpw(2,h2),mo-2)%mo;
	if(n>60)
	{		std::cout<<fm<<' '<<fm;
		return 0;
	}
	else
	{
		ll l=fpw(2,n)-k+1;
		ll r=fpw(2,n);
		if(r>=mo) r=mo-1;
		if(l>r)
		{
			std::cout<<fm<<' '<<fm;
			return 0;
		}
		ll ans=1;
		for(int i=l;i<=r;i++)
			ans=ans*i%mo;
		
		ll fz=(ans*fpw(fpw(2,h2),mo-2))%mo;
		 fz=(fm-fz+mo)%mo;
		std::cout<<fz<<' '<<fm;
	}
}