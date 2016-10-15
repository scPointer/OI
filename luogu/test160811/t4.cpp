#include <cstdio>
#include <algorithm>
#define N 100050
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define lowbit(x) ((x)&(-x))
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
struct Point{int lvl,stg,tel,atk;}po[N];
bool cmplvl(Point a,Point b){return a.lvl<b.lvl;}
bool cmpatk(Point a,Point b){return a.atk<b.atk;}
bool cmpstg(Point a,Point b){return a.stg<b.stg;}
int hh[N*5],hcnt;
int n;
int getHash(int p)
{
	int l=1,r=hcnt+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(p<hh[mid]) r=mid;
		else l=mid;
	}
	return l;
}
void initHash()
{
	std::sort(hh+1,hh+1+hcnt);
	int p=1;
	for(int i=2;i<=hcnt;i++)
		if(hh[i]!=hh[i-1])
			hh[++p]=hh[i];
	hcnt=p;
}
int dp[N];
int mx[N*5],vis[N*5],tip;
void update(int p,int v)
{
	for(;p<=hcnt;p+=lowbit(p))
		if(vis[p]!=tip) vis[p]=tip,mx[p]=v;
		else mx[p]=Max(mx[p],v);
}
int getmax(int p)
{
	int res=0;
	for(;p;p-=lowbit(p))
		if(vis[p]==tip)
			res=Max(res,mx[p]);
	return res;
}
void cdq(int l,int r)
{
	if(l==r){return;}
	int mid=(l+r)>>1;
	cdq(l,mid);
	std::sort(po+l,po+1+mid,cmpatk);
	std::sort(po+1+mid,po+1+r,cmpstg);
	++tip;
	int ptr=l;
	for(int i=mid+1,res;i<=r;i++)
	{
		while(ptr<=mid && po[ptr].atk<=po[i].stg)
		{
			update(po[ptr].tel,dp[po[ptr].lvl]);
			++ptr;
		}
		res=getmax(po[i].atk);
		dp[po[i].lvl]=Max(dp[po[i].lvl],res+1);
	}
	std::sort(po+l,po+1+r,cmplvl);
	cdq(mid+1,r);
}
int main()
{
//	freopen("t4.in","r",stdin);
	n=RD();
	for(int i=1;i<=n;i++)
	{
		po[i].lvl=RD();po[i].stg=RD();po[i].tel=RD();po[i].atk=RD();
		hh[++hcnt]=po[i].stg;
		hh[++hcnt]=po[i].tel;
		hh[++hcnt]=po[i].atk;
	}
	initHash();
	std::sort(po+1,po+1+n,cmplvl);
	for(int i=1;i<=n;i++)
	{
		po[i].stg=getHash(po[i].stg);
		po[i].tel=getHash(po[i].tel);
		po[i].atk=getHash(po[i].atk);
		po[i].lvl=i;
	}
	for(int i=1;i<=n;i++) dp[i]=1;
	cdq(1,n);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=Max(ans,dp[i]);
	printf("%d",ans);
}
