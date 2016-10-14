#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define N 1000005
int dis[N],cnt[N],a[N];
int main()
{
	srand(time(NULL));
	freopen("1096.in","w",stdout);
	int n=5;
	for(int i=1;i<=n;i++)
		dis[i]=rand(),cnt[i]=rand(),a[i]=rand();
	dis[1]=0;
	std::sort(dis+1,dis+1+n);
	
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d %d\n",dis[i],cnt[i],a[i]);
}
