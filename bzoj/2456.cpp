#include <cstdio>
int sz[33];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		for(int j=0;p;j++,p>>=1)
			if(p&1) sz[j]++;
	}
	int ans=0;
	for(int i=0,j=1;i<=31;i++,j<<=1)
		if(sz[i]>(n>>1)) ans+=j;
	printf("%d",ans);
}