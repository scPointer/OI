#include <cstdio>
#define MAXN 500005
int cd[MAXN];
int n,l;
int main()
{
	int si,di,mincd=1000000050;
	scanf("%d%d",&n,&l);
	if(n==1){printf("1");return 0;}
	
	scanf("%d",&di);
	for(int i=2;i<=n;i++)
	{
		scanf("%d%d",&si,&di);
		cd[i]=cd[i-1]+si-di;
		if(cd[i]<mincd) mincd=cd[i];
	}
	scanf("%d",&si);
	
	for(int i=1;i<=n;i++)
		if(cd[i]==mincd)
			printf("%d ",i);
	return 0;
}
