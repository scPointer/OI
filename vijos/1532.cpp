#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 50005
#define MAXR 50005
struct request{int l,r,num;}rq[MAXN];
int last[MAXN];
int tr[MAXR];
int n,maxr,ans;
bool cmp(request a,request b)
{
	if(a.l<=b.l)
		return a.r<=b.r;
	else return a.r<b.r;
}
void addin(int p)
{
	for(;p<=maxr;p+=p&(-p))
		tr[p]++;
}
int gotsum(int p)
{
	int ret=0;
	for(;p>0;p-=p&(-p))
		ret+=tr[p];
	return ret;
}
int find(int p)
{
	if(last[p]==p) return p;
	else return last[p]=find(last[p]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&rq[i].l,&rq[i].r,&rq[i].num);
		rq[i].l++;rq[i].r++;
		if(rq[i].r>maxr) maxr=rq[i].r;
	}
	for(int i=1;i<=maxr;i++)
		last[i]=i;
	sort(rq+1,rq+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int needtoput=rq[i].num-(gotsum(rq[i].r)-gotsum(rq[i].l-1));
		if(needtoput<=0) continue;
		ans+=needtoput;
		int p=rq[i].r;
		do
		{
			p=find(p);
			if(p<rq[i].l){printf("-1");return 0;}
			addin(p);
			last[p]=p-1;
			p--;
		}while(--needtoput>0);
	}
	printf("%d",ans);
	return 0;
}
