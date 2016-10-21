#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int rd32(){return (rand()<<15)|rand();}
int main()
{
	freopen("chocolatebox.in","w",stdout);
	srand(time(NULL));
	int n=10;//00000;
	int m=10;//00000;
	int k=rd32();
	int p1=1000000007;
	int p2=1000000007;
	printf("%d %d %d %d %d\n",n,m,k,p1,p2);
	for(int i=1;i<=n;i++)
		printf("%d ",rd32());
	puts("");
	for(int i=1;i<=m;i++)
	{
		int tp=rd32()%2+1;
		int l=rd32()%n+1;
		int r=rd32()%n+1;
		if(l>r) swap(l,r);
		printf("%d %d %d\n",tp,l,r);
	}
}