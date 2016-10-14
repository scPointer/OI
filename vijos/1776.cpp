#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 20005
#define MAXM 100005
struct ctd{//contradiction
	int p1,p2;
	int w;
}pri[MAXM];
int dset[MAXN*2];
int n,m;
int find(int p){return p==dset[p]?p:dset[p]=find(dset[p]);}
bool cmp(ctd a,ctd b){return a.w>b.w;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*2;i++)
		dset[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&pri[i].p1,&pri[i].p2,&pri[i].w);
	sort(pri+1,pri+1+m,cmp);
	int i;
	for(i=1;i<=m;i++)
	{
		int p1_at1=find(pri[i].p1);
		int p1_at2=find(pri[i].p1+n);
		int p2_at1=find(pri[i].p2);
		int p2_at2=find(pri[i].p2+n);
		if(p1_at1==p2_at1||p1_at2==p2_at2)
			break;
		dset[p1_at1]=p2_at2;
		dset[p1_at2]=p2_at1;
	}
	printf("%d",pri[i].w);
	return 0;
}
