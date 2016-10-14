#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 501
struct task{
	int ti,punish;
}ta[MAXN];
bool used[MAXN];
int cmp(task a,task b)
{
	return a.punish>b.punish;
}
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&ta[i].ti);
	for(int i=1;i<=n;i++)
		scanf("%d",&ta[i].punish);
	sort(ta+1,ta+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int p=ta[i].ti;
		while(p>0&&used[p]==1) --p;
		if(p==0) ans+=ta[i].punish;
		else used[p]=1;
	}
	printf("%d",ans);
	return 0;
}
