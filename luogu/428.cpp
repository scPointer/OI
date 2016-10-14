#include <cstdio>
#define MAXN 105
int p[MAXN],n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		int ans=0;
		for(int j=i-1;j>=1;j--)
			if(p[j]<p[i]) ans++;
		printf("%d ",ans);
	}
	return 0;
}
