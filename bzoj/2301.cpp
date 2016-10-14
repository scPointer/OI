#include <cstdio>
#define N 50005
#define Min(a,b) (a<b?a:b)
int miu[N],sum[N];
int prime[N],pcnt;
bool notprime[N];
int n;
void getmiu(int n)
{
	miu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!notprime[i])
		{
			miu[i]=-1;
			prime[++pcnt]=i;
		}
		for(int j=1;prime[j]*i<=n;j++)
		{
			notprime[prime[j]*i]=1;
			if(i%prime[j]==0)
			{
				miu[i*prime[j]]=0;
				break;
			}
			miu[i*prime[j]]=-miu[i];
		}
	}
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+miu[i];
}
int calc(int x,int y)
{
	int rez=0;
	for(int i=1,last;i<=x && i<=y;i=last+1)
	{
		last=Min(x/(x/i),y/(y/i));
		rez+=(x/i)*(y/i)*(sum[last]-sum[i-1]);
	}
	return rez;
}
int main()
{
	scanf("%d",&n);
	getmiu(50000);
	for(int i=1,a,b,c,d,k;i<=n;i++)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%d\n",calc(b/k,d/k)-calc((a-1)/k,d/k)-calc(b/k,(c-1)/k)+calc((a-1)/k,(c-1)/k));
	}
	return 0;
}
