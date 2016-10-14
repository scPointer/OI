#include <cstdio>
#include <algorithm>
#define N 10000005
typedef long long ll;
int fac[N],inv[N];
bool noprm[N];
int mo;
int fpw(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=(ll)res*a%mo;
		a=(ll)a*a%mo;
		b>>=1;
	}
	return res;
}
void init(int lim)
{
	for(int i=2;i<=lim;i++)
		if(noprm[i]==0 && (ll)i*i<=lim)
		{
			for(int j=i*i;j<=lim;j+=i)
				noprm[j]=1;
		}
	fac[0]=1;
	for(int i=1;i<=lim;i++)
		fac[i]=(ll)fac[i-1]*i%mo;
	inv[1]=1;
	for(int i=2;i<=lim;i++)
		if(noprm[i])
			inv[i]=inv[i-1];
		else
			inv[i]=(ll)inv[i-1]*(i-1)%mo*fpw(i,mo-2)%mo;
}

int main()
{
	int T;scanf("%d%d",&T,&mo);
	init(10000000);
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		int ans=(ll)fac[n]*inv[m]%mo;
		printf("%d\n",ans);
	}
}
