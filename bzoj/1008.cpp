#include <iostream>
#define MO 100003
using namespace std;
long long calc(long long a,long long ep)
{
	long long rez=1;
	while(ep)
	{
		if(ep&1) rez=(rez*a)%MO;
		ep>>=1;a=(a*a)%MO;
	}
	return rez;
}
int main()
{
	long long m,n,ans;
	cin>>m>>n;
	ans=((calc(m,n)-m*calc(m-1,n-1))%MO+MO)%MO;
	cout<<ans;
	return 0;
}
