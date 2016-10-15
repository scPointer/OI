#include <cstdio>
#include <algorithm>
int n;
int a[100005];
int geth(int p)
{
	int l=0,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(a[mid]>p) r=mid;
		else l=mid;
	}
	return l;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	std::sort(a+1,a+1+n);
	int q;scanf("%d",&q);
	while(q--)
	{
		int p;scanf("%d",&p);
		printf("%d\n",geth(p));
	}
}
