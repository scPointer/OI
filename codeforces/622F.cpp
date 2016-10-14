#include <cstdio>
#define mo 1000000007
#define N 1000050
typedef long long ll;
int pd[N];
int fac[N],inv[N];
int pre[N];
int fpw(int a,int b)
{
	int res=1;
	for(;b;b>>=1)
	{
		if(b&1) res=(ll)res*a%mo;
		a=(ll)a*a%mo;
	}
	return res;
}
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	pd[0]=n;fac[0]=1;inv[0]=1;pre[0]=0;
	for(int i=1;i<=k+1;i++)
	{
		pd[i]=(ll)pd[i-1]*(n-i)%mo;
		fac[i]=(ll)fac[i-1]*i%mo;
		inv[i]=fpw(fac[i],mo-2);
		pre[i]=(pre[i-1]+fpw(i,k))%mo;
	}
	if(n<=k+1)
	{
		printf("%d",pre[n]);
		return 0;
	}
	int ans=0,res;
	for(int i=0;i<=k+1;i++)
	{
		res=(ll)pd[k+1]*fpw(n-i,mo-2)%mo*pre[i]%mo*inv[i]%mo*inv[k+1-i]%mo;
		if((k+1-i)&1) res=mo-res;
		ans=(ans+res)%mo;
	}
	printf("%d",ans);
}
