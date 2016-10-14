#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int main()
{
	freopen("2038.in","w",stdout);
	srand(time(NULL));
	int n=1;
	int m=500;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%n+1);
	puts("");
	for(int i=1;i<=m;i++)
	{
		int p1=rand()%n+1,p2=rand()%n+1;
		if(p1>p2) std::swap(p1,p2);
		printf("%d %d\n",p1,p2);
	}
	
}