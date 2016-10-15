#include <cstdio>
#include <algorithm>
int a[700005];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	std::sort(a+1,a+1+n);
	printf("%d",a[(n+1)>>1]);
}