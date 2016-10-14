#include <cstdio>
#define MAXN 505
int n,p;
int dset[MAXN],dtr[MAXN];
int height;
int find(int p)
{
	if(dset[p]==p)
		height=0;
	else
	{
		dset[p]=find(dset[p]);
		height+=dtr[p];
		dtr[p]=height;
	}
	return dset[p];
}
int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
		dset[i]=i;
	int numofsets=n;
	for(int i=1;i<=p;i++)
	{
		int p1,p2,dis;
		scanf("%d%d%d",&p1,&p2,&dis);
		int fp1=find(p1);
		int fp2=find(p2);
		if(fp1==fp2)
		{
			if(dtr[p2]-dtr[p1]!=dis){printf("-1");return 0;}
		}
		else
		{
			numofsets--;
			dset[fp2]=fp1;
			dtr[fp2]=dtr[p1]+dis-dtr[p2];
		}
	}
	if(numofsets>1){printf("-1");return 0;}
	int minh=0;
	for(int i=1;i<=n;i++)
	{
		find(i);
		if(dtr[i]<minh) minh=dtr[i];
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",dtr[i]-minh);
	return 0;
}
