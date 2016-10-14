#include <cstdio>
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
inline int RC()
{
	char cr;
	while( (cr=getchar())<'A' || cr>'Z');
	return cr;
}
#define N 2005
#define QUE 1000005
#define lowbit(x) (x&(-x))
typedef long long ll;
struct garland{
	int len;
	int x[N],y[N],w[N];
}gl[N];
struct Query{
	bool tp;
	int x1,y1,x2,y2;
}query[QUE];
int ask[N],askcnt;
ll mp[N][N];
ll ans[N][N];
bool on[N];
int n,m,k;
void add(int x,int y,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			mp[i][j]+=val;
}
ll sum(int x,int y)
{
	ll res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=mp[i][j];
	return res;
}
int main()
{
	n=RD();m=RD();k=RD();
	for(int i=1;i<=k;i++)
	{
		garland& g=gl[i];
		g.len=RD();
		for(int j=g.len;j>=1;j--)
		{
			g.x[j]=RD();
			g.y[j]=RD();
			g.w[j]=RD();
		}
	}
	int q=RD();
	for(int i=1;i<=q;i++)
		if(RC()=='A')
		{
			Query& que=query[i];
			que.tp=1;
			ask[++askcnt]=i;
			que.x1=RD();
			que.y1=RD();
			que.x2=RD();
			que.y2=RD();
		}
		else
			query[i].x1=RD();
	for(int i=1;i<=k;i++)
	{
		garland& g=gl[i];
		for(int j=g.len;j>=1;j--)
			add(g.x[j],g.y[j],g.w[j]);
		for(int j=1;j<=askcnt;j++)
		{
			Query& que=query[ask[j]];
			ans[i][j]=sum(que.x2,que.y2)+sum(que.x1-1,que.y1-1)-sum(que.x1-1,que.y2)-sum(que.x2,que.y1-1);
		}
		for(int j=g.len;j>=1;j--)
			add(g.x[j],g.y[j],-g.w[j]);
	}
	for(int i=1;i<=k;i++)
		on[i]=1;
	
	int pos=0;
	for(int i=1;i<=q;i++)
	{
		Query& que=query[i];
		if(que.tp==0)
			on[que.x1]^=1;
		else
		{
			ll prt=0;
			++pos;
			for(int j=1;j<=k;j++)
				if(on[j])
					prt+=ans[j][pos];
			printf("%I64d\n",prt);
		}
	}
}
