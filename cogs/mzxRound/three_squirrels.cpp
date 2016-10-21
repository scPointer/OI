#include <cstdio>
#define N 100005
#define mo 1000000007
typedef long long ll;
int cnt[N];
int inc[N][11];
int has[N];
bool vis[N];
int dfs(int p)
{
	if(vis[p]) return has[p];
	vis[p]=1;
	for(int i=1;i<=cnt[p];i++)
		has[p]=((ll)has[p]+dfs(inc[p][i]))%mo;
	return has[p];
}
int main()
{
	freopen("three_squirrels.in","r",stdin);
	freopen("three_squirrels.out","w",stdout);
	has[0]=1;vis[0]=1;
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&cnt[i]);
		for(int j=1;j<=cnt[i];j++)
			scanf("%d",&inc[i][j]);
	}
	printf("%d",dfs(n));
}