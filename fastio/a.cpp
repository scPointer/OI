#include <cstdio>
#include <ctime>
int main()
{
	freopen("x.in","r",stdin);
	int c1=clock();
	int n;
	scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
		scanf("%d",&p);
	printf("%d\n",clock()-c1);
}