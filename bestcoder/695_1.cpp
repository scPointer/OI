#include <cstdio>
#define N 1000005
#define MO 1000000007
long long f[N];

int main()
{
	f[0]=1;f[1]=1;
	for(int i=2;i<=1000000;i++)
		f[i]=(f[i-1]+f[i-2]*(i-1))%MO;
	int T,n;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&n);
		printf("Case #%d:\n%d\n",i,(int)f[n]);
	}
}