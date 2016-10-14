#include <cstdio>
#include <ctime>
#include <cstdlib>
//int rand()
//{
//	static long long x=36823,a=783417,b=99975443,mo=1000000009;
//	return x=(x*a+b)%mo;
//}
int c[11][11];
int main()
{
	freopen("3925.txt","w",stdout);
	srand(time(NULL));
	int n=rand()%9+2;
	int m=rand()%(n*(n-1)/2)+1;
	printf("%d %d\n",n,m);
	for(int i=1,p1,p2;i<=m;i++)
	{
		p1=rand()%n+1,p2=rand()%n+1;
		while(p1==p2 || c[p1][p2]==1) p1=rand()%n+1,p2=rand()%n+1;
		c[p1][p2]=c[p2][p1]=1;
		printf("%d %d\n",p1,p2);
	}
}