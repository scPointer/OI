#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
int rd32(){return (rand()<<15)|rand();}
int main()
{
	freopen("chenyao_fib_game.in","w",stdout);
	int n=100000;
	int m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;i++)
	{
		int tp=rd32()%2;
		int l=rd32()%n+1;
		int r=rd32()%n+1;
		if(l>r) std::swap(l,r);
		if(tp) printf("%d %d %d\n",tp,l,r);
		else printf("%d %d\n",tp,l);
	}
}
