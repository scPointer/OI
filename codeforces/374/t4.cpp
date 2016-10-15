#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Node{
	ll val;
	int id;
	int sign;
	bool operator<(const Node& b)const{return b.val<val;}
};
priority_queue<Node> pq;
ll ans[200005];
int getsn(int p)
{
	if(p>0) return 1;
	else if(p==0) return 0;
	else return -1;
}
int main()
{
	int n,k,x;scanf("%d%d%d",&n,&k,&x);
	int sn=1,zeros=0;
	for(int i=1;i<=n;i++)
	{
		int v;scanf("%d",&v);
		if(v==0) zeros++;
		if(v<0) sn*=-1;
		pq.push((Node){v*getsn(v),i,getsn(v)});
	}
	for(int i=1;i<=k;i++)
	{
		Node p=pq.top();pq.pop();
		if(p.sign==0)
		{
			if(zeros>1 || sn==-1)
			{
				p.sign=1;
				p.val=x;
			}
			else
			{
				sn=-sn;
				p.sign=-1;
				p.val=x;
			}
			pq.push(p);
			--zeros;
		}
		else
		{
			if(sn==1)
			{
				p.val-=x;
				if(p.val==0)
				{
					if(p.sign==-1) sn=-sn;
					p.sign=0,zeros++;
				}
				else if(p.val<0) p.val=-p.val,p.sign=-p.sign,sn=-sn;
			}
			else
			{
				p.val+=x;
			}
			pq.push(p);
		}
//		printf("%I64d %d %d\n",p.val,p.sign,p.id);
	}
	for(int i=1;i<=n;i++)
	{
		Node p=pq.top();pq.pop();
		ans[p.id]=p.val*p.sign;
	}
	for(int i=1;i<=n;i++)
		printf("%I64d ",ans[i]);
}
