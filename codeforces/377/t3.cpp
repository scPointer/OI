#include <iostream>
#include <algorithm>
#define mabs(x) ((x)>0?(x):-(x))
using namespace std;
typedef long long ll;
ll a,b,c;
ll check(ll p1,ll p2,ll p3)
{
	return mabs(a-p1)+mabs(b-p2)+mabs(c-p3);
}
int main()
{
	cin>>a>>b>>c;
	if(a==b && b==c){cout<<0;return 0;}
	if(a>b) swap(a,b);
	if(a>c) swap(a,c);
	if(b>c) swap(b,c);
	if(b==c){cout<<mabs(c-a)-1;return 0;}
	ll ans=check(c-1,c-1,c);
	cout<<ans;
	return 0;
}
