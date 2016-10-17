#include <cstdio>
#include <algorithm>
#define N 200005
struct Node{int id,v,link,use;}cmp[N],sok[N];
bool compare(Node a,Node b){return a.v<b.v;}
bool compid(Node a,Node b){return a.id<b.id;}
int n,m;
int check(int p)
{
	int l=1,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(cmp[mid].v<p || (cmp[mid].v==p && !cmp[mid].link)) l=mid;
		else r=mid;
	}
	if(cmp[l].v==p && !cmp[l].link) return l;
	else return -1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&cmp[i].v);
		cmp[i].id=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&sok[i].v);
		sok[i].id=i;
	}
	std::sort(cmp+1,cmp+1+n,compare);
	std::sort(sok+1,sok+1+m,compare);
	int cntans=0,cntused=0;
	for(int i=1;i<=m;i++)
	{
		int used=0;
		int val=sok[i].v;
		while(1)
		{
			int res=check(val);
			if(res!=-1)
			{
				cntans++;
				cntused+=used;
				sok[i].use=used;
				sok[i].link=res;
				cmp[res].link=sok[i].id;
				break;
			}
			if(val<=1) break;
			val=(val+1)>>1;
			++used;
		}
	}
	std::sort(cmp+1,cmp+1+n,compid);
	std::sort(sok+1,sok+1+m,compid);
	printf("%d %d\n",cntans,cntused);
	for(int i=1;i<=m;i++)
	{
		printf("%d",sok[i].use);
		if(i<m) printf(" ");
		else printf("\n");
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d",cmp[i].link);
		if(i<n) printf(" ");
		else printf("\n");
	}
}