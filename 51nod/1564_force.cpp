#include <cstdio>
#define N 100005
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
long long a[N],n;
long long solve(int p)
{
//	if(p%20==0) printf("solve%d\n",p);
	long long ans=0;
	for(int i=1;i<=n-p+1;i++)
	{
		long long mn=a[i],mx=a[i];
		for(int j=i;j<=i+p-1;j++)
		{
			mn=Min(mn,a[j]);
			mx=Max(mx,a[j]);
		}
		if(mn*mx>ans)
		{
			ans=mn*mx;
			printf("upd %lld*%lld from %d-%d\n",mn,mx,i,i+p-1);
		}
//		ans=Max(ans,mn*mx);
	}
	return ans;
}
int main()
{
	long long x=0;
	freopen("p1564.in","r",stdin);
	freopen("p1564.ans","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		long long ans=solve(i);
		printf("%d %lld\n",i,ans);
		x^=ans;
	}
	printf("%lld",x);
}