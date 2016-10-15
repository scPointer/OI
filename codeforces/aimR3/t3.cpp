#include <cstdio>

int main()
{
	int n,b,d;scanf("%d%d%d",&n,&b,&d);
	int cnt=0,sum=0;
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		if(p>b) continue;
		sum+=p;
		if(sum>d)
		{
			sum=0;
			cnt++;
		}
	}
	printf("%d",cnt);
}
