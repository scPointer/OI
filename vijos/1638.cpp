#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 500050
struct tube{
	long long x,y;
}tb[MAXN];
long long h[MAXN];

int n;
long long x0,y0;
bool cmp(tube a,tube b)
{
	if(a.x!=b.x) return a.x<b.x;
	else return a.y<b.y;
}
int main()
{
	scanf("%lld%lld",&x0,&y0);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&tb[i].x,&tb[i].y);
	sort(tb+1,tb+1+n,cmp);
	
	int ans=1;
	h[1]=tb[1].y;
	for(int i=2;i<=n;i++)
	{
		int l=0,r=ans+1,mid;
		while(l<r-1)
		{
			mid=(l+r)/2;
			if(tb[i].y>=h[mid]) l=mid;
			else r=mid;
		}
		h[l+1]=tb[i].y;
		if(l+1>ans) ans=l+1;
	}
	printf("%d",ans);
	return 0;
}
