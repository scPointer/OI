#include <cstdio>
#define N 100005
int a[N];
int d[N];
int last[N];
int pre[N];
int n,m;
bool check(int p)
{
	if(p==n+1) return 1;
	for(int i=1;i<=m;i++)
		last[i]=0;
	for(int i=1;i<=p;i++)
		pre[i]=0;
	for(int i=p;i>=1;i--)
		if(d[i] && last[d[i]]==0)
			last[d[i]]=i,pre[i]=a[d[i]];
	for(int i=1;i<=m;i++)
		if(!last[i]) return 0;
	int cnt=0;
	for(int i=1;i<=p;i++)
	{
		if(!pre[i]) cnt++;
		else cnt-=pre[i];
		if(cnt<0) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	int l=0,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	int ans;
	if(r==n+1) ans=-1;
	else ans=r;
	printf("%d",ans);
}