#include <cstdio>
#include <algorithm>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
typedef long long ll;
#define N 250005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define Swap(a,b) std::swap(a,b)
#define INF 10000000000000000ll
int eg[N<<1],nxt[N<<1],head[N],we[N<<1],egtot;
int fa[N][19],h[N];
ll dp[N];
int dfo[N],timetip;
int rd[N],q[N],stk[N],top;
int fson[N],bro[N],tim[N];

int n,MAXF;
inline bool cmp(int a,int b){return dfo[a]<dfo[b];}
void addEdge(int p1,int p2,int w)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	we[egtot]=w;
	head[p1]=egtot;
}
void setTree(int p)
{
	dfo[p]=++timetip;
	for(int i=1;i<=MAXF;i++)
		if(fa[p][i-1]==1) fa[p][i]=1;
		else fa[p][i]=fa[fa[p][i-1]][i-1];
	for(int i=head[p],pt;i;i=nxt[i])
		if(eg[i]!=fa[p][0])
		{
			pt=eg[i];
			fa[pt][0]=p;
			h[pt]=h[p]+1;
			dp[pt]=Min(dp[p],we[i]);
			setTree(pt);
		}
}
int lca(int a,int b)
{
	if(h[a]<h[b]) Swap(a,b);
	for(int i=0,dis=h[a]-h[b];dis;i++,dis>>=1)
		if(dis&1)
			a=fa[a][i];
	if(a==b) return a;
	for(int i=MAXF;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
void addSon(int f,int s)
{
	if(tim[f]<timetip)
		tim[f]=timetip,fson[f]=bro[f]=0;
	if(tim[s]<timetip)
		tim[s]=timetip,fson[s]=bro[s]=0;
	bro[s]=fson[f];
	fson[f]=s;
}
ll dfs(int p)
{
	ll res=0;
	for(int i=fson[p];i;i=bro[i])
		res+=dfs(i);
	if(res==0) return dp[p];
	else return p==1?res:Min(res,dp[p]);
}
int main()
{
	n=RD();
	for(int i=n;i;i>>=1) MAXF++;
	for(int i=1,p1,p2,w;i<=n-1;i++)
	{
		p1=RD();p2=RD();w=RD();
		addEdge(p1,p2,w);
		addEdge(p2,p1,w);
	}
	fa[1][0]=1;dp[1]=INF;
	setTree(1);
	for(int m=RD();m;m--)
	{
		++timetip;
		
		int k=RD();
		for(int i=1;i<=k;i++)
			rd[i]=RD();
		std::sort(rd+1,rd+1+k,cmp);
		
		int p=1;
		for(int i=2;i<=k;i++)
			if(lca(rd[i],rd[p])!=rd[p])
				rd[++p]=rd[i];
		k=p;
		
		stk[top=1]=1;
		for(int i=1;i<=k;i++)
		{
			p=lca(stk[top],rd[i]);
			while(1)
			{
				if(stk[top]==p)
				{
					stk[++top]=rd[i];
					break;
				}
				else if(p==stk[top-1])
				{
					addSon(stk[top-1],stk[top]);
					stk[top]=rd[i];
					break;
				}
				else if(h[p]>h[stk[top-1]])
				{
					addSon(p,stk[top]);
					stk[top]=p;
					stk[++top]=rd[i];
					break;
				}
				else
				{
					addSon(stk[top-1],stk[top]);
					top--;
				}
			}
		}
		for(int i=1;i<=top-1;i++)
			addSon(stk[i],stk[i+1]);
		ll ans=dfs(1);
		printf("%lld\n",ans);
	}
}
