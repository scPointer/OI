#include <cstdio>
int n,c,ans;
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		int j=i;
		while(j>0)
		{
			if(j%10==c)
				ans++;
			j/=10;
		}
	}
	printf("%d",ans);
	return 0;
}
