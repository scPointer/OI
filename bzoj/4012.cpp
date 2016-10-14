#include <cstdio>
#include <algorithm>
#define N 150005
#define Q 200005
#define ND 20000005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
struct Age{
	int sc,id;
	friend bool operator<(Age a,Age b){return a.sc==b.sc? a.id<b.id: a.sc<b.sc;}
}ag[N];
int n;
inline int findbound(int p)
{
	int l=0,r=n,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(ag[mid].sc>=p) r=mid;
		else l=mid;
	}
	return r;
}
inline int findupper(int p)
{
	int l=1,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(ag[mid].sc<=p) l=mid;
		else r=mid;
	}
	return l;
}
int eg[N*2],pto[N*2],nxt[N*2],dist[N*2],head[N],egtot;
void addEdge(int p1,int p2,int dis)
{
	egtot++;
	eg[egtot]=p2;
	nxt[egtot]=head[p1];
	dist[egtot]=dis;
	head[p1]=egtot;
}
int sz[N],fa[N],pson[N],distofa[N];
int dfo[N],top[N],idcnt;
long long esum[N],distort[N],sumdis[N];
void dfs(int p)
{
	sz[p]=1;
	for(int i=head[p],pt;i;i=nxt[i])
		if(eg[i]!=fa[p])
		{
			pt=eg[i];
			fa[pt]=p;
			distofa[pt]=dist[i];
			distort[pt]=distort[p]+dist[i];
			dfs(pt);
			sz[p]+=sz[pt];
			if(sz[pt]>sz[pson[p]])
				pson[p]=pt;
		}
}
void dfs2(int p,int tp)
{
	dfo[p]=++idcnt;
	esum[idcnt]=distofa[p];
	top[p]=tp;
	if(pson[p]!=0) dfs2(pson[p],tp);
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa[p] && eg[i]!=pson[p])
			dfs2(eg[i],eg[i]);
}
int rot[N],ls[ND],rs[ND],ct[ND],ndcnt;
long long sum[ND];
int update(int prt,int gl,int gr,int ll,int rr)
{
	int rt=++ndcnt;
	ls[rt]=ls[prt];rs[rt]=rs[prt];ct[rt]=ct[prt];sum[rt]=sum[prt];
	if(gl==ll && gr==rr){ct[rt]++;return rt;}
	sum[rt]+=esum[gr]-esum[gl-1];
	int mid=(ll+rr)/2;
	if(gr<=mid) ls[rt]=update(ls[rt],gl,gr,ll,mid);
	else if(gl>mid) rs[rt]=update(rs[rt],gl,gr,mid+1,rr);
	else ls[rt]=update(ls[rt],gl,mid,ll,mid),rs[rt]=update(rs[rt],mid+1,gr,mid+1,rr);
	return rt;
}
long long getsum(int p,int gl,int gr,int ll,int rr)
{
	long long res=(esum[gr]-esum[gl-1])*ct[p];
	if(gl==ll && gr==rr)
		return sum[p]+res;
	int mid=(ll+rr)/2;
	if(gr<=mid) return res+getsum(ls[p],gl,gr,ll,mid);
	else if(gl>mid)return res+getsum(rs[p],gl,gr,mid+1,rr);
	else return res+getsum(ls[p],gl,mid,ll,mid) + getsum(rs[p],mid+1,gr,mid+1,rr);
}
long long query(int rt,int p)
{
	long long res=0;
	while(top[p]!=1){res+=getsum(rt,dfo[top[p]],dfo[p],1,n);p=fa[top[p]];}
	res+=getsum(rt,1,dfo[p],1,n);
	return res;
}
int main()
{
	int Qs,lim;
	scanf("%d%d%d",&n,&Qs,&lim);
	for(int i=1;i<=n;i++){
		scanf("%d",&ag[i].sc);
		ag[i].id=i;
	}
	std::sort(ag+1,ag+1+n);
	for(int i=1,p1,p2,dis;i<=n-1;i++)
	{
		scanf("%d%d%d",&p1,&p2,&dis);
		addEdge(p1,p2,dis);
		addEdge(p2,p1,dis);
	}
	distort[1]=0;esum[0]=0;
	dfs(1);
	dfs2(1,1);
	for(int i=1;i<=n;i++) esum[i]+=esum[i-1];
	for(int i=1;i<=n;i++) sumdis[i]=sumdis[i-1]+distort[ag[i].id];
	for(int i=1,p;i<=n;i++)
	{
		p=ag[i].id; rot[i]=rot[i-1];
		while(top[p]!=1){rot[i]=update(rot[i],dfo[top[p]],dfo[p],1,n);p=fa[top[p]];}
		rot[i]=update(rot[i],1,dfo[p],1,n);
	}
	long long preans=0;
	for(int i=1,mise,ra,rb,ll,rr;i<=Qs;i++)
	{
		scanf("%d%d%d",&mise,&ra,&rb);
		ll=Min((preans+ra)%lim,(preans+rb)%lim);
		rr=Max((preans+ra)%lim,(preans+rb)%lim);
		ll=findbound(ll);
		rr=findupper(rr);
		printf("%lld\n",(preans=(sumdis[rr]-sumdis[ll-1])+distort[mise]*(rr-ll+1)-(query(rot[rr],mise)-query(rot[ll-1],mise))*2));
	}
}
