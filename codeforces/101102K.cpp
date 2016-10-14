#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define N 100005
#define ls p<<1
#define rs (p<<1)+1
#define Min(a,b) (a<b?a:b)
#define pb push_back
#define debug(x) printf("%s=%d\n",#x,x)
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int mxid[N*8];
int minv[N*8],prev[N*8];
int deg[N];
inline void pushdown(int p) 
{
	if(prev[p])
	{
		minv[p]+=prev[p];
		prev[ls]+=prev[p];
		prev[rs]+=prev[p];
		prev[p]=0;
	}
}
inline void update(int p)
{
	int lv=minv[ls]+prev[ls];
	int rv=minv[rs]+prev[rs];
	minv[p]=Min(lv,rv);
	if(lv<rv)
		mxid[p]=mxid[ls];
	else
		mxid[p]=mxid[rs];
}
void initTree(int p,int l,int r)
{
	if(l==r) mxid[p]=l,minv[p]=deg[l],prev[p]=0;
	else
	{
		int mid=(l+r)>>1;
		initTree(ls,l,mid);
		initTree(rs,mid+1,r);
		update(p);
	}	
}
void modify(int p,int l,int r,int gl,int gr,int v)
{
	if(l!=r) pushdown(p);
	if(l==gl && r==gr)
	{
		prev[p]+=v;
		if(l!=r) pushdown(p);
		else
		{
			minv[p]+=prev[p];
			prev[p]=0;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(gr<=mid) modify(ls,l,mid,gl,gr,v);
	else if(gl>mid) modify(rs,mid+1,r,gl,gr,v);
	else modify(ls,l,mid,gl,mid,v),modify(rs,mid+1,r,mid+1,gr,v);
	update(p);
}
vector<int> eg[N];
int main()
{
	int T=RD();
	while(T--)
	{
		int n,m;n=RD();m=RD();
		for(int i=1;i<=n;i++)
			eg[i].resize(0);
		memset(deg,0,sizeof(deg));
		memset(mxid,0,sizeof(mxid));
		memset(minv,0,sizeof(minv));
		memset(prev,0,sizeof(prev));
		for(int i=1;i<=n;i++)
			deg[i]=i-1;
		for(int i=1,p1,p2;i<=m;i++)
		{
			p1=RD();p2=RD();
			eg[p1].pb(p2);
			deg[p2]--;
		}
		initTree(1,1,n);
		for(int i=1;i<=n;i++)
		{
			printf("%d ",mxid[1]);
			int p=mxid[1];
			modify(1,1,n,p,p,1000000);
			eg[p].pb(p);
			eg[p].pb(n+1);
			std::sort(eg[p].begin(),eg[p].end());
			for(int j=eg[p].size()-1;j>=1;j--)
			{
				int r=eg[p][j]-1;
				int l=eg[p][j-1]+1;
				if(l<=r) modify(1,1,n,l,r,-1);
			}
		}
		puts("");
	}
}
