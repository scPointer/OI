#include <cstdio>
#define MAXN 1505
#define MIN(a,b) (a<b?a:b)
#define INF 2147483647
struct tree{
//	int dad;
	int fstson;
	int fare;
}po[MAXN];
int nxtson[MAXN];
int hasdad[MAXN];
int minf[MAXN][3];
void minfare(int p)
{
	if(po[p].fstson==0)
	{
		minf[p][0]=po[p].fare;
		minf[p][1]=INF;
		minf[p][2]=0;
		return;
	}
//	minf[p][1]+=po[p].fare;
	int flag=INF;
	int ns=po[p].fstson;
	while(ns!=0)
	{
		minfare(ns);
		minf[p][0]+=MIN(minf[ns][0],MIN(minf[ns][1],minf[ns][2]));
		minf[p][1]+=MIN(minf[ns][0],minf[ns][1]);
		minf[p][2]+=MIN(minf[ns][1],minf[ns][0]);
		if(flag>minf[ns][0]-minf[ns][1])
			flag=minf[ns][0]-minf[ns][1];
		ns=nxtson[ns];
	}
	minf[p][0]+=po[p].fare;
	if(flag>0) minf[p][1]+=flag;
/*	ns=po[p].fstson;
	int nmin=minf[p][1]-minf[ns][1]+minf[ns][2];
//	int flag=0;
	while(ns!=0)
	{
		if(minf[p][1]-minf[ns][1]+minf[ns][2]<nmin)
			nmin=minf[p][1]-minf[ns][1]+minf[ns][2];
//		if(minf[ns][1]==minf[ns][2]) flag=1;
		ns=nxtson[ns];
	}
//	if(flag=0)
		minf[p][1]=nmin;
	if(minf[p][2]<minf[p][1])
		minf[p][1]=minf[p][2];
*/
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int id,fare,nsons;
		scanf("%d%d%d",&id,&fare,&nsons);
		po[id].fare=fare;
		int ls,ns;
		if(nsons==0) continue;
		scanf("%d",&ns);
		po[id].fstson=ns;
		hasdad[ns]=1;
		for(int j=2;j<=nsons;j++)
		{
			ls=ns;
			scanf("%d",&ns);
			nxtson[ls]=ns;
			hasdad[ns]=1;
		}
	}
	int root=0;
	for(int i=1;i<=n;i++)
		if(hasdad[i]==0)
		{root=i;minfare(i);break;}
	printf("%d",MIN(minf[root][1],minf[root][0]));
	return 0;
}
