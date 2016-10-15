#include <cstdio>
#include <iostream>
long long ans1,ans2;
void solve(long long p)
{
	if(p%2==1)
	{
		ans1=((long long)p*p)/2;
		ans2=ans1+1;
	}
	else
	{
		solve(p/2);
		ans1*=2;
		ans2*=2;
	}
}
int main()
{
	int n;scanf("%d",&n);
	if(n<=2){puts("-1");return 0;}
	solve(n);
	std::cout<<ans1<<' '<<ans2;
}