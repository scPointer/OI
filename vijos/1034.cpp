#include <cstdio>
#define MAXN 5001
int dset[MAXN];
int n,m,q;
int find(int p)
{
	if(p!=dset[p]) dset[p]=find(dset[p]);
	return dset[p];
}
void check(int a,int b)
{
	int da=find(a),db=find(b);
	if(da==db) printf("Yes\n");
	else printf("No\n");
}
void join(int a,int b)
{
	int da=find(a),db=find(b);
	if(da!=db)
		dset[da]=db;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
		dset[i]=i;
	for(int i=1;i<=m;i++)
	{
		int ra,rb;
		scanf("%d%d",&ra,&rb);
		join(ra,rb);
	}
	for(int i=1;i<=q;i++)
	{
		int ra,rb;
		scanf("%d%d",&ra,&rb);
		check(ra,rb);
	}
}
