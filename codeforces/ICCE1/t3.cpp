#include <cstdio>
#define N 100005
#define Max(a,b) (a>b?a:b)
typedef long long ll;
int n;
int a[N];
int odr[N];
ll ans[N];
ll val[N];
int dset[N];
bool used[N];
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&odr[i]);
	for(int i=1;i<=n;i++)
		dset[i]=i,val[i]=a[i];
	ll now=0;
	for(int i=n;i>=1;i--)
	{
		ans[i]=now;
		int p=odr[i];used[p]=1;
		if(used[p-1])
		{
			int f1=find(p-1);
			int f2=find(p);
			dset[f2]=f1;
			val[f1]=val[f1]+val[f2];
		}
		if(used[p+1])
		{
			int f1=find(p+1);
			int f2=find(p);
			dset[f2]=f1;
			val[f1]=val[f1]+val[f2];
		}
		now=Max(now,val[find(p)]);
	}
	for(int i=1;i<=n;i++)
		printf("%I64d\n",ans[i]);
}
