#include <cstdio>
#define N 10000005
#define MO 20101009
#define PRM 664579
#define Min(a,b) (a<b?a:b)
long long mu[N];
bool notprm[N];
int prm[PRM+2],pcnt;
void mobius(int lim)
{
	for(int i=1;i<=lim;i++) mu[i]=0;
	mu[1]=1;
	for(int i=2;i<=lim;i++)
	{
		if(notprm[i]==0)
		{
			prm[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;i*prm[j]<=lim;j++)
		{
			if(i%prm[j]==0)
			{
				notprm[i*prm[j]]=1;
				mu[i*prm[j]]=0;
				break;
			}
			mu[i*prm[j]]=-mu[i];
			notprm[i*prm[j]]=1;
		}
	}
	mu[0]=0;
	for(int i=1;i<=lim;i++)
		mu[i]=(mu[i-1]+(long long)i*i*mu[i])%MO;
}
inline long long getg(long long x,long long y)
{
	x=(x*(x+1)/2)%MO;
	y=(y*(y+1)/2)%MO;
	return (x*y)%MO;
}
long long getf(int a,int b)
{
	if(a>b) a^=b^=a^=b;
	long long miu,res=0;
	for(int i=1,last=0;i<=a;i=last+1)
	{
		i=Min(a/(a/i),b/(b/i));
		miu=((mu[i]-mu[last])%MO+MO)%MO;
		miu=(miu*getg(a/i,b/i))%MO;
		res=(res+miu)%MO;
		last=i;
	}
	return res;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	if(n>m) n^=m^=n^=m;
	mobius(n);
	long long ans=0,res;
	for(int i=1,last=0;i<=n;i=last+1)
	{
		i=Min(n/(n/i),m/(m/i));
		res=getf(n/i,m/i)%MO;
		res=(res*(i+last+1)*(i-last)/2)%MO;
		ans=(ans+res)%MO;
		last=i;
	}
	printf("%lld",ans);
}
