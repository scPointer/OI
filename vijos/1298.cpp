#include <cstdio>
#include <algorithm>
int a[10005];
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(n&1){printf("lolanv\n");continue;}
		std::sort(a+1,a+1+n);
		int cnt=0;
		for(int i=1;i<=n;i+=2)
			cnt+= a[i]==a[i+1];
		printf("%s\n",cnt==n/2? "Wind":"lolanv");
	}
}