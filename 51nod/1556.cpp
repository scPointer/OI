#include <cstdio>
#define N 1000050
#define MO 1000000007
#define M(a) (a=(a%MO+MO)%MO)
int n;
long long mk[N],f,exp3,err,ans;
int main()
{
	scanf("%d",&n);
	--n;
	if(!n){printf("1");return 0;}
	mk[0]=1;mk[1]=1;err=0;ans=1;
	for(int i=2;i<=n;i++)
	{
		ans*=3;M(ans);
		mk[i]=((mk[i-1]*(long long)(2*i+1)+mk[i-2]*(long long)(3*i-3))/(i+2));
		M(mk[i]);
	}
	ans*=3;M(ans);
	exp3=1;
	for(int i=n-1;i>=0;i--)
	{
		err+=exp3*mk[i];M(err);
		exp3*=3;M(exp3);
	}
	ans-=err;M(ans);
	printf("%lld\n",ans);
	return 0;
}
