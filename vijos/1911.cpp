#include <cstdio>
#define N 105
#define LIM 20005
int a[N];
bool aru[LIM];
int n,cnt;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		aru[a[i]]=1;
	}
	for(int i=1;i<=n-1;i++)
		for(int j=i+1;j<=n;j++)
			if(aru[a[i]+a[j]]){cnt++;aru[a[i]+a[j]]=0;}
	printf("%d",cnt);
	return 0;
}

