#include <cstdio>
typedef long long ll;
#define mod 10000003
int a[10000005];
int gethash(int p)//141 387876
{
	int x=p;
	ll a=875353;
	ll b=1348798;
	while(1)
	{
		p=(((ll)p*a+b)%mod+mod)%mod;
		if(a[p]==0)
		{
			a[p]=x;
			break;
		}
	}
}
bool query(int p)
{
	int x=p;
	ll a=875353;
	ll b=1348798;
	while(1)
	{
		p=(((ll)p*a+b)%mod+mod)%mod;
		if(a[p]==x) return 1;
		else if(a[p]==0) break;
	}
	return 0;
}
//a[i]=j    i->j
//j的hash值是i
int main()
{
	
}