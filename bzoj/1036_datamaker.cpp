#include <cstdio>
#include <cstdlib>
#include <ctime>
#define N 155
int dset[N];
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
int main()
{
	freopen("1036.in","w",stdout);
	srand(time(NULL));
	int n=8,m=100;
	for(int i=1;i<=n;i++) dset[i]=i;
	
	printf("%d\n",n);
	for(int i=1;i<=n-1;)
	{
		int p1=rand()%n+1;
		int p2=rand()%n+1;
		if(find(p1)!=find(p2))
		{
			dset[find(p1)]=find(p2);
			printf("%d %d\n",p1,p2);
			i++;
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",rand()%n*2-n);
	printf("\n%d\n",m);
	for(int i=1;i<=m;i++)
	{
		int tp=rand()%3;
		if(tp==0) printf("CHANGE ");
		else if(tp==1) printf("QMAX ");
		else printf("QSUM ");
		printf("%d ",rand()%n+1);
		if(tp==0) printf("%d\n",rand()%n*2-n);
		else printf("%d\n",rand()%n+1);
	}
}
