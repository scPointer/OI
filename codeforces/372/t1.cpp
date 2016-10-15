#include <cstdio>
typedef long long ll;
int main()
{
	int n;scanf("%d",&n);
	ll last=2;
	for(int i=1;i<=n;i++)
	{
		ll ned=(ll)i*(i+1)*(i+1);
		printf("%I64d\n",ned-last);
		last=(ll)i;
	}
}
