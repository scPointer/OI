#include <cstdio>
#include <cstring>
#include <cmath>
#define MA 1011
int n;
struct edge{
	int pst;
	int pto;
	int next;
}ed[MA*MA+16];
int head[MA*2+2],edtop;
int vis[MA*2+2];
int match[MA*2+2];
bool ifprime(int a)
{
	for(int i=2;i<=(int)sqrt(a);i++)
		if(a%i==0) return false;
	return true;
}
void joinedge(int p,int q)
{
	edtop++;
	ed[edtop].pst=p;
	ed[edtop].pto=q;
	ed[edtop].next=head[p];
	head[p]=edtop;

}
bool dfs(int p)
{
	for(int k=head[p];ed[k].pto!=0;k=ed[k].next)
		if(vis[ed[k].pto]==0)
		{
			vis[ed[k].pto]=1;
			if(match[ed[k].pto]==0||dfs(match[ed[k].pto])==1)
			{
				match[ed[k].pto]=p;
				match[p]=ed[k].pto;
				return true;
			}
		}
	return false;
}
bool xyl(int p)
{
	memset(ed,0,sizeof(ed));
	memset(head,0,sizeof(head));
	for(int i=1;i<=p;i++)
		for(int j=1;j<=n;j++)
			joinedge(i,p+j);
	for(int i=1;i<=p;i++)
		for(int j=1;j<i;j++)
			if(ifprime(i+j)) joinedge(i,p+j+n);
	
	memset(match,0,sizeof(match));
	
	for(int i=1;i<=p;i++)
		if(match[i]==0)
		{
			memset(vis,0,sizeof(vis));
			vis[i]=1;
			if(dfs(i)==0) return false;
		}
	return true;
}
int main()
{
	scanf("%d",&n);
	int l=1,r=MA,mid;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(xyl(mid)==1)
			l=mid;
		else r=mid;
	}
	int ans;
	if(xyl(r)==1) ans=r;
	else ans=l;
	printf("%d",ans);
	return 0;
}
