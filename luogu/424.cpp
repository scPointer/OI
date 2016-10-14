#include <iostream>
using namespace std;
int main()
{
	int a,b;
	long long ans=0;
	cin>>a>>b;
	ans=(long long)(b/7)*1250;
	b%=7;
	for(int i=1;i<=b;i++)
	{
		if(a<=5) ans+=250;
		a=a%7+1;
	}
	cout<<ans;
	return 0;
}
