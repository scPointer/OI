#include<bits/stdc++.h>
int main()
{
	long long g,l,T;
	scanf("%lld",&T);
	while(~scanf("%lld%lld",&g,&l))
		printf("%lld %lld\n",(long long)sqrt(l/g)*g*2,g+l);
	return 0;
}