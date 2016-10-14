#include <cstdio>
#include <vector>
using namespace std;
#define N 100005
#define NDS (115*N)
#define pb push_back
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
struct Num{
	unsigned char a;
	unsigned short int b;
//	void operator=(const Num& ot){a=ot.a;b=ot.b;}
	inline int chs(){return ((int)a<<16)+b;}
}ls[NDS],rs[NDS],rot[N];
int ccnt;
bool ir[NDS];
unsigned short int cnt[NDS];
const unsigned short int lim=65535;
int query(Num rt,int p,int bs=30)
{
	if(bs==-1 || rt.chs()==0) return cnt[rt.chs()]+(ir[rt.chs()]<<16);
	if((p>>bs)&1) return query(rs[rt.chs()],p,bs-1);
	else return query(ls[rt.chs()],p,bs-1);
}
Num add(Num rt,int p,int bs=30)
{
	int nrt=++ccnt;
	if(cnt[rt.chs()]<lim) cnt[nrt]=cnt[rt.chs()]+1,ir[nrt]=ir[rt.chs()];
	else cnt[nrt]=0,ir[nrt]=1;
	if(bs==-1) return (Num){nrt>>16,nrt&lim};
	if((p>>bs)&1)
	{
		ls[nrt]=ls[rt.chs()];
		rs[nrt]=add(rs[rt.chs()],p,bs-1);
	}
	else
	{
		ls[nrt]=add(ls[rt.chs()],p,bs-1);
		rs[nrt]=rs[rt.chs()];
	}
	return (Num){nrt>>16,nrt&lim};
}


int dset[N],sz[N];
int dfind(int p){return dset[p]==p? p:dset[p]=dfind(dset[p]);}
void merge(int p1,int p2){dset[p1]=p2;sz[p2]+=sz[p1];}

struct Edge{int pfr,pto,w;}eg[N<<1];
int nxt[N<<1],head[N],egtot;
void addEdge(int p1,int p2,int w)
{
	eg[++egtot]=(Edge){p1,p2,w};
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}

int fa[N],h[N];
int wi[N];
void dfs(int p)
{
	for(int i=head[p];i;i=nxt[i])
	{
		Edge& e=eg[i];
		if(e.pto!=fa[p])
		{
			fa[e.pto]=p;
			h[e.pto]=h[p]+1;
			wi[e.pto]=wi[p]^e.w;
			dfs(e.pto);
		}
	}
}

int odr[N];
long long ans[N];
int last[N],val[N],fs[N],tail[N];
int main()
{
	freopen("u4733.in","r",stdin);
	int n=RD();
	for(int i=1,p1,p2,w;i<=n-1;i++)
	{
		p1=RD();p2=RD();w=RD();
		addEdge(p1,p2,w);
		addEdge(p2,p1,w);
	}
	for(int i=1;i<=n-1;i++)
		odr[i]=RD();
	fa[1]=1;
	dfs(1);
	
	rot[0]=add((Num){0,0},0);
	for(int i=1;i<=n;i++)
		dset[i]=i,sz[i]=1,rot[i]=rot[0],tail[i]=fs[i]=i;
	for(int i=n-1;i>=1;i--)
	{
		ans[i]=ans[i+1];
		int p1=dfind(eg[odr[i]<<1].pfr);
		int p2=dfind(eg[odr[i]<<1].pto);
		if(sz[p1]>sz[p2]) swap(p1,p2);
		int trs=wi[p1]^wi[p2];
		for(int j=fs[p1];j;j=last[j])
			ans[i]+=query(rot[p2],val[j]^=trs);
		for(int j=fs[p1];j;j=last[j])
			rot[p2]=add(rot[p2],val[j]);
		last[tail[p2]]=fs[p1];
		tail[p2]=tail[p1];
		merge(p1,p2);
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
}