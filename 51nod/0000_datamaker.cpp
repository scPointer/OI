#include <cstdio>
#include <ctime>
#include <cstdlib>
int p[77];
int main()
{
	srand(time(NULL));
	freopen("p0000.in","w",stdout);
	int n=50;
	int m=20;
	int maxt=50;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
	{
//		int cnt=rand()%maxt+1;
		int cnt=maxt;
		printf("%d\n",cnt);
		int sum=10000;
		for(int j=1;j<=cnt-1;j++)
		{
			p[j]=rand()%200;
//			p[j]=200;
			sum-=p[j];
		}
		p[cnt]=sum;
		for(int j=1;j<=cnt;j++)
			printf("%d %d\n",rand()%1000+1,p[j]);
	}
}