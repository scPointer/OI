#include <cstdio>
int a[505];
int b[505];
int res[505];
int n,k;
int solve(int p)
{
	int sum=p-a[1];
	b[1]=p;
	for(int i=2;i<=n;i++)
	{
		if(b[i-1]+a[i]<k)
			b[i]=k-b[i-1];
		else b[i]=a[i];
		sum+=b[i]-a[i];
	}
	return sum;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int ans=10000003;
	for(int i=a[1];i<=k || i==a[1];i++)
	{
		int ret=solve(i);
		if(ret<ans)
		{
			ans=ret;
			for(int j=1;j<=n;j++)
				res[j]=b[j];
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<n;i++)
		printf("%d ",res[i]);
	printf("%d",res[n]);
}
