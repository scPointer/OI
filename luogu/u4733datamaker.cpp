#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define N 100005
int a[N];
int main()
{
	srand(time(NULL));
	freopen("u4733.in","w",stdout);
	int n=80000;
	int shuffle=100000;
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %d %d\n",i,rand()%(i-1)+1,rand()%1);
	for(int i=0;i<=n-2;i++)
		a[i]=i+1;
	for(int i=1;i<=shuffle;i++)
		std::swap(a[rand()%(n-1)],a[rand()%(n-1)]);
	for(int i=0;i<=n-2;i++)
		printf("%d ",a[i]);
}