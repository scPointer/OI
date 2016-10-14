#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
int main()
{
	freopen("5152.in","w",stdout);
	srand(time(NULL));
	int n=12;
	int swords=7;
	printf("%d\n",swords);
	int a[24];
	for(int i=0;i<24;i++) a[i]=i;
	for(int i=1;i<=2000;i++)
	{
		int p1=rand()%24;
		int p2=rand()%24;
		swap(a[p1],a[p2]);
	}
	for(int i=0;i<12;i++)
		if(a[i<<1]>a[(i<<1)+1])
			swap(a[i<<1],a[(i<<1)+1]);
	for(int i=0;i<n;i++)
		printf("%d,%d,%d %d,%d,%d\n",a[i<<1],rand()%80+1,rand()%50+1,a[(i<<1)+1],rand()%80+1,rand()%50+1);
}