#include <cstdio>
#include <queue>
#define Max(a,b) (a>b?a:b)
#define N 100100
using namespace std;
struct Node{
	long long wi,hei,cnt;
//	Node(long long _w=0,long long _h=0):wi(_w),hei(_h){}
};
inline bool operator<(Node a,Node b){return a.wi!=b.wi? a.wi>b.wi: a.hei>b.hei;}
priority_queue<Node> q;

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	long long rd,totalsum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&rd);
		totalsum+=rd;
		q.push((Node){rd,0,rd});
	}
	if(n==1)
	{
		printf("%lld\n%lld\n",totalsum,1ll);
		return 0;
	}
	int res=(k-1-(n-1)%(k-1))%(k-1);
	for(int i=n+1;i<=n+res;i++)
		q.push((Node){0,0,0});
	n+=res;
	for(int i=(n-1)/(k-1);i>=1;i--)
	{
		Node nd;
		long long maxh=0,sumw=0,sumans=0;
		for(int j=1;j<=k;j++)
		{
			nd=q.top(); q.pop();
			sumw+=nd.wi;
			sumans+=nd.cnt;
			maxh=Max(maxh,nd.hei);
		}
		q.push((Node){sumw,maxh+1,sumans+sumw});
	}
	Node nd=q.top();
	printf("%lld\n%lld\n",nd.cnt-totalsum,nd.hei);
}