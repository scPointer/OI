#include <cstdio>
#include <queue>
using namespace std;
#define N 2000005
#define M 6000005
#define INF 2100000001
int n,m,S,T;
int eg[M],wei[M],nxt[M],head[N],egtot;
queue<int> q;
bool inq[N];
int dist[N];
inline int RD(){static int res;scanf("%d",&res);return res;}
inline int Point(int x,int y,bool t)
{
	static int res;
	if(x==n || y==0) return S;
	else if(x==0 || y==m) return T;
	res=(x-1)*m+y;
	if(t) res+=n*m;
	return res;
}
void addEdge(int p1,int p2,int w)
{
//	printf("addEdge %d %d with %d\n",p1,p2,w);
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	wei[egtot]=w;
	head[p1]=egtot;
	
	eg[++egtot]=p1;
	nxt[egtot]=head[p2];
	wei[egtot]=w;
	head[p2]=egtot;
}
int spfa(int s,int t)
{
	for(int i=1;i<=t;i++) dist[i]=INF;
	dist[s]=0;
	q.push(s);inq[s]=1;
	while(!q.empty())
	{
		int p=q.front();q.pop();inq[p]=0;
		for(int e=head[p];e;e=nxt[e])
			if(dist[p]+wei[e]<dist[eg[e]])
			{
				dist[eg[e]]=dist[p]+wei[e];
				if(!inq[eg[e]]) inq[eg[e]]=1,q.push(eg[e]);
			}
	}
	return dist[t];
}
int main()
{
	n=RD();m=RD();
	S=n*m*2+1;T=S+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m-1;j++)
			addEdge( Point(i-1,j,1) , Point(i,j,0) ,RD());
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m;j++)
			addEdge( Point(i,j-1,0) , Point(i,j,1) ,RD());
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m-1;j++)
			addEdge( Point(i,j,0) , Point(i,j,1) ,RD());
	printf("%d",spfa(S,T));
	return 0;
}
