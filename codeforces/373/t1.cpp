#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define N 20//0005
#define M 20//05
typedef long long ll;
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
int n,m;
int pa[N];
int st[N];
struct Node{
	int val,pf;
	bool operator<(const Node& b)const{return val>b.val;}
};
struct Query{
	int v,id;
	bool operator<(const Query& b)const{return v<b.v;}
}q[M];
ll ans[M];
ll check(ll tim)
{
	ll res=0;
	for(int i=1;i<=n;i++)
		if(tim>=st[i]) res+=(tim-st[i])/pa[i];
		else break;
	return res;
}
void solve(int l,int r,ll tl,ll tr)
{
	if(l>r || tl>tr) return;
	else if(tl==tr)
	{
		for(int i=l;i<=r;i++)
			ans[q[i].id]=tl;
		return;
	}
	ll tmid=(tl+tr)>>1;
	ll res=check(tmid);
	int ll=l-1,rr=r+1
	,mid;
	while(ll<rr-1)
	{
		mid=(ll+rr)>>1;
		if(q[mid].v<=res) ll=mid;
		else rr=mid;
	}
	mid=ll;
	solve(l,mid,tl,tmid);
	solve(mid+1,r,tmid+1,tr);
}
priority_queue<Node> pq;
int main()
{
	n=RD();
	m=RD();
	for(int i=1;i<=n;i++)
		pa[i]=RD();
	std::sort(pa+1,pa+1+n);
	st[1]=0;
	pq.push((Node){pa[1],pa[1]});
	for(int i=2;i<=n;i++)
	{
		Node nd=pq.top();
		pq.pop();
		st[i]=nd.val;
		nd.val+=nd.pf;
		pq.push(nd);
		pq.push((Node){st[i]+pa[i],pa[i]});
	}
	for(int i=1;i<=m;i++)
	{
		q[i].id=i;
		q[i].v=RD();
	}
	std::sort(q+1,q+1+m);
	solve(1,m,0,10ll);
	for(int i=1;i<=m;i++)
		printf("%I64d\n",ans[i]);
}
