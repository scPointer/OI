#include <cstdio>
#include <algorithm>
using namespace std;
#define N 50005
#define INF ((1<<31)-1)
int a[N];
int n,k;
inline int find(int p)
{
	int l=0,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(a[mid]>p) r=mid;
		else l=mid;
	}
	return r;
}
bool check(int p)
{
	int cow=0,pos=1;
	while(cow<=k && pos<=n)
		cow++,pos=find(a[pos]+p+p);
	return cow<=k? 1:0;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	a[n+1]=INF;
	sort(a+1,a+1+n);
	int l=-1,r=a[n]-a[1],mid;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%d",r);
	return 0;
}
