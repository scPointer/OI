#include <cstdio>
#define N 10005
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
typedef long long ll;
ll pi[N],si[N];
ll giveout[N];
int n,c;
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%I64d",&pi[i]);
	for(int i=1;i<=n;i++)
		scanf("%I64d",&si[i]);
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		giveout[i]=(ll)(i-1)*c+pi[i]-si[i];
		if(giveout[i]<0) giveout[i]=0;
		ll mn=Min(pi[i],si[i]);
		ans+=mn;
		pi[i]-=mn;
		si[i]-=mn;
	}
	for(int i=1;i<=n;i++)
	{
		if(pi[i]<=si[i])
		{
			ans+=pi[i];
			continue;
		}
		ans+=si[i];
		pi[i]-=si[i];
		for(int j=i+1;j<=n;j++)
		{
			int could=Min(0,Min(
		}
	}
	for(int i=n;i>=1;i--)
	{
		if(pi[i]>=si[i])
		{
			ans+=si[i];
			continue;
		}
		ans+=pi[i];
		si[i]-=pi[i];
		for(int j=i-1;j>=1;j--)
		{
			int could=Min(Min(pi[j],c),giveout[j]);
			if(could<si[i])
			{
				pi[j]-=could;
				giveout[j]-=could;
				si[i]-=could;
				ans+=could;
			}
			else
			{
				ans+=si[i];
				pi[j]-=si[i];
				giveout[j]-=si[i];
				si[i]=0;
				break;
			}
		}
	}
	printf("%I64d\n",ans);
}
