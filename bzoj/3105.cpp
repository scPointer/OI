#include <cstdio>
#include <algorithm>
#define N 105
int a[N],set[N];
int main()
{
//	freopen("3105.in","r",stdin);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	std::sort(a+1,a+1+n);
	long long ans=0;
	for(int i=1;i<=n;i++) set[i]=a[i],ans+=a[i];
	for(int i=n;i>=1;i--)
		if(a[i])
		{
			ans-=set[i];
			int p=-1;
			for(int j=29;j>=0;j--)
				if(a[i]&(1<<j)){p=j;break;}
			for(int j=i-1;j>=1;j--)
				if(a[j]&(1<<p))
					a[j]^=a[i];
		}
	printf("%lld",ans);
}