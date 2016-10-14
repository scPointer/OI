#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 1200000+5
struct STree{
	int lmax,rmax,sum,amax;
}tr[MAXN*4];
int ni[MAXN];
int n,m;
void Update(int p)
{
	tr[p].lmax=max(tr[p*2].lmax,tr[p*2].sum+tr[p*2+1].lmax);
	tr[p].rmax=max(tr[p*2+1].rmax,tr[p*2+1].sum+tr[p*2].rmax);
	tr[p].sum=tr[p*2].sum+tr[p*2+1].sum;
	tr[p].amax=max(tr[p*2].rmax+tr[p*2+1].lmax,max(tr[p*2].amax,tr[p*2+1].amax));
}
void SetTree(int l,int r,int p)
{
	if(l==r)
	{
		tr[p].sum=ni[l];
//		if(ni[l]>=0) 
			tr[p].lmax=tr[p].rmax=tr[p].amax=ni[l];
//		else tr[p].lmax=tr[p].rmax=tr[p].amax=0;
		return;
	}
	int mid=(l+r)/2;
	SetTree(l,mid,p*2);
	SetTree(mid+1,r,p*2+1);
	Update(p);
}
void find(int l,int r,int p)
{
	printf("%d-%d lmax:%d rmax:%d amax:%d sum:%d\n",
			l,r,tr[p].lmax,tr[p].rmax,tr[p].amax,tr[p].sum);
	int mid=(l+r)/2;
	if(l!=r)
	{
		find(l,mid,p*2);
		find(mid+1,r,p*2+1);
	}
}
void change(int l,int r,int p,int& we,int& goal)
{
	if(l==r)
	{
		tr[p].sum=goal;
//		if(goal>=0) 
			tr[p].lmax=tr[p].rmax=tr[p].amax=goal;
//		else tr[p].lmax=tr[p].rmax=tr[p].amax=0;
		return;
	}
	int mid=(l+r)/2;
	if(we<=mid) change(l,mid,p*2,we,goal);
	else change(mid+1,r,p*2+1,we,goal);
	Update(p);
}
STree solve(int l,int r,int p,int gl,int gr)
{
	if(gl==l&&gr==r)
		return tr[p];
	int mid=(l+r)/2;
	if(gr<=mid)
		return solve(l,mid,p*2,gl,gr);
	else if(gl>mid)
		return solve(mid+1,r,p*2+1,gl,gr);
	else
	{
		STree ans1=solve(l,mid,p*2,gl,mid);
		STree ans2=solve(mid+1,r,p*2+1,mid+1,gr);
		STree ans;
		ans.sum=ans1.sum+ans2.sum;
		ans.lmax=max(ans1.lmax,ans1.sum+ans2.lmax);
		ans.rmax=max(ans2.rmax,ans2.sum+ans1.rmax);
		ans.amax=max(ans1.rmax+ans2.lmax,max(ans1.amax,ans2.amax));
		return ans;
	}
}
int main()
{
//	freopen("b.in6","r",stdin);
//	freopen("b.ou6","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&ni[i]);
	SetTree(1,n,1);
//	find(1,n,1);
	for(int i=1;i<=m;i++)
	{
		int d,k1,k2;
		scanf("%d%d%d",&d,&k1,&k2);
		if(d==2)
			change(1,n,1,k1,k2);
		else
		{
			if(k1>k2) k1^=k2^=k1^=k2;
			STree ans=solve(1,n,1,k1,k2);
			printf("%d\n",ans.amax);
		}
	}//516178590523
	return 0;
}
