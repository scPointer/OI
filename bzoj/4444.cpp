#include <cstdio>
#include <algorithm>
//using namespace std;
#define N 800050
int hash[N],hcnt,pre[N],pcnt;
int dp[N];
struct Line{int l,r,id;}line[N];
int lcnt;
int fson[N],bro[N],fa[N][19];
int lfa[N];
int delta[N];
int ans[N];
bool cmp(Line a,Line b){return a.l<b.l;}
int check(int p)
{
	static int l,r,mid;
	l=1,r=hcnt;
	while(l<r)
	{
		mid=(l+r)/2;
		if(hash[mid]<p) l=mid+1;
		else if(hash[mid]>p) r=mid-1;
		else return mid;
	}
	return l;
}
int main()
{
//	freopen("4444.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1,ll,rr;i<=n;i++)
	{
		scanf("%d%d",&ll,&rr);
		if(rr<ll) rr+=m;
		line[++lcnt]=(Line){ll,rr,i};
		pre[++pcnt]=ll;pre[++pcnt]=rr;
		line[++lcnt]=(Line){ll+m,rr+m,i+n};
		pre[++pcnt]=ll+m;pre[++pcnt]=rr+m;
	}
	
	std::sort(pre+1,pre+1+pcnt);pre[0]=-1;
	for(int i=1;i<=pcnt;i++)
		if(pre[i]!=pre[i-1]) hash[++hcnt]=pre[i];
		
	std::sort(line+1,line+1+lcnt,cmp);
	for(int i=1;i<=lcnt;i++)
		line[i].l=check(line[i].l),line[i].r=check(line[i].r);
	for(int i=1,top=1;i<=lcnt;i++)
	{
		while(top<=lcnt && line[top].l<=line[i].r) top++;
		fa[i][0]=top-1;
	}
	for(int i=1;i<=lcnt;i++)
		if(line[i].id>n) delta[line[i].id-n]=line[i].l;
	
	int L=0;
	for(int i=1;line[i].r<delta[line[1].id];i=fa[i][0]) L++;
	L--;
	for(int i=1;i<=lcnt;i++) lfa[i]=L%2==0?i:fa[i][0];
	for(int i=1,j=2;i<=18 && j<=L;i++,j<<=1)
		for(int p=1;p<=lcnt;p++)
		{
			fa[p][i]=fa[fa[p][i-1]][i-1];
			if(L&(1<<i)) lfa[p]=lfa[fa[p][i]];
		}
	for(int i=1,j;i<=lcnt;i++)
		if(line[i].id<=n)
		{
			for(j=0;j<=2;j++)
				if(line[lfa[i]].r>=delta[line[i].id]) break;
				else lfa[i]=fa[lfa[i]][0];
			ans[line[i].id]=L+j+1;
		}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
}
