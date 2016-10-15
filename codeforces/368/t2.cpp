#include <cstdio>
#define N 300005
#define INF 1000000007
#define Min(a,b) (a<b?a:b)
int pfr[N],pto[N],len[N];
bool isk[N];
int main()
{
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&pfr[i],&pto[i],&len[i]);
	for(int i=1,p;i<=k;i++)
	{
		scanf("%d",&p);
		isk[p]=1;
	}
	int ans=INF;
	for(int i=1;i<=m;i++)
		if(isk[pfr[i]]^isk[pto[i]]==1)
		{
			ans=Min(ans,len[i]);
		}
	if(ans==INF) printf("-1");
	else printf("%d",ans);
		
}