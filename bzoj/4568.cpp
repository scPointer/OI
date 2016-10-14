#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20005
#define L 60
#define Swap(a,b) std::swap(a,b)
typedef long long ll;
inline ll RD()
{
	static ll res;
	static char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
ll st[16][N][L],tem[L];
int fa[16][N],h[N];
void merge(ll* a,ll* b)
{
	for(int i=L-1;i>=0;i--)
		if(b[i])
		{
			ll x=b[i];
			for(int j=L-1;j>=0;j--)
				if(x&(1ll<<j))
				{
					if(a[j]) x^=a[j];
					else
					{
						a[j]=x;
						break;//???
					}
				}
		}
}
int eg[N*2],nxt[N*2],head[N],egtot;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
void dfs(int p)
{
	for(int i=head[p];i;i=nxt[i])
		if(fa[0][p]!=eg[i])
		{
			fa[0][eg[i]]=p;
			h[eg[i]]=h[p]+1;
			dfs(eg[i]);
		}
}
void setSTtable(int n)
{
	for(int i=1;i<=14;i++)
		for(int j=1;j<=n;j++)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	for(int i=1;i<=14;i++)//WA: for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(fa[i-1][j])//WA: if(fa[i][j])
			{
				memcpy(st[i][j],st[i-1][j],sizeof(st[i][j]));
				merge(st[i][j],st[i-1][fa[i-1][j]]);//WA: st[i][j],st[i-1][fa[i][j]]
			}
}
int lca(int a,int b)
{
	if(h[a]<h[b]) Swap(a,b);
	for(int delta=h[a]-h[b],i=0;delta;delta>>=1,i++)
		if(delta&1) a=fa[i][a];
	for(int i=14;i>=0;i--)
		if(fa[i][a]!=fa[i][b])
		{
			a=fa[i][a];
			b=fa[i][b];
		}
	return a==b? a: fa[0][a];
}
int lg2[N];
void calc(ll* t,int p,int len)
{
	if(len<=0) return;
	for(int i=0;len;len>>=1,i++)
	if(len&1){merge(t,st[i][p]);p=fa[i][p];}
}
int main()
{
	int n,q; n=RD();q=RD();
	for(int i=1;i<=n;i++) lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=n;i++)
	{
		tem[0]=RD();
		merge(st[0][i],tem);
	}
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		p1=RD();p2=RD();
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	h[1]=1;dfs(1);
	setSTtable(n);
	for(int i=1,p1,p2,lc;i<=q;i++)
	{
//		printf("run %d\n",i);
		p1=RD();p2=RD();
		lc=lca(p1,p2);
		memset(tem,0,sizeof(tem));
		calc(tem,p1,h[p1]-h[lc]+1);
		calc(tem,p2,h[p2]-h[lc]);
		ll ans=0;
		for(int j=L-1;j>=0;j--)
			if((ans^tem[j])>ans)
				ans^=tem[j];
		printf("%lld\n",ans);
	}
	
}