#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
int main()
{
	freopen("4521.in","w",stdout);
	srand(time(NULL));
	int T=1000000;
	int n=11;
	long long l,r;
	printf("%d\n",T);
	for(int i=1;i<=T;i++)
	{
		l=rand()%9+1,r=rand()%9+1;
		for(int i=1;i<=n-1;i++)
			l=l*10+rand()%10,r=r*10+rand()%10;
		if(l>r) std::swap(l,r);
		printf("%lld %lld\n",l,r);
	}
}