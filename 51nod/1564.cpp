#include <cstdio>
//#include <ctime>
//#include <iostream>
//#include <algorithm>
#define N 100005
#define NDS 2000005
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
inline int RD()
{
	static int res;
	static char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
/*
struct Node{
	int v,id;
	bool operator<(const Node& b)const{return v<b.v;}
}nd[N];
bool cmp(const Node& a,const Node& b){return a.id<b.id;}
*/
//int ls[NDS],rs[NDS],ct[NDS],rot[N],rid[N],ndcnt;
//int v[N],id[N],ls[N],rs[N];
//int nearval,nid;
//int fol[N];
int pos[17][N],mn[17][N],mx[17][N],lg2[N];
int a[N];
int n;
/*void find(int p,int rt)
{
	if(rt==0) return ;
	if(p<v[rt])
	{
		if(ls[rt]!=0) find(p,ls[rt]);
		else if(nid==0) nid=-rt;
	}
	else
	{
		if(v[rt]>nearval)
		{
			nearval=v[rt];
			nid=rt;
		}
		if(rs[rt]!=0) find(p,rs[rt]);
	}
}
void initFollow(int n)
{
	for(int i=1;i<=n;i++) v[i]=a[i];
	for(int i=n-1;i>=1;i--)
	{
		nearval=0;nid=0;
		find(a[i],n);
		if(nid<0) fol[i]=n+1,ls[-nid]=i;
		else fol[i]=nid,rs[nid]=i;
	}
}
*/

inline int getpos(int l,int r)
{
	int lg=lg2[r-l+1]-1;
	int mid=r-(1<<lg)+1;
	return mn[lg][l]<mn[lg][mid]? pos[lg][l]: pos[lg][mid];
}
inline int getmax(int l,int r)
{
	int lg=lg2[r-l+1]-1;
	int mid=r-(1<<lg)+1;
	return mx[lg][l]>mx[lg][mid]? mx[lg][l]: mx[lg][mid];
}
void initST(int n)
{
	for(int i=1;i<=n;i++) lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=n;i++) mn[0][i]=mx[0][i]=a[i],pos[0][i]=i;
	for(int j=1;(1<<j)<=n;j++)
	{
		int x=1<<(j-1);
		for(int i=1;i<=n;i++)
		{
			if(mn[j-1][i]<mn[j-1][i+x])
				mn[j][i]=mn[j-1][i],pos[j][i]=pos[j-1][i];
			else
				mn[j][i]=mn[j-1][i+x],pos[j][i]=pos[j-1][i+x];
			mx[j][i]=Max(mx[j-1][i],mx[j-1][i+x]);
		}
	}
}
/*
int check(int lrt,int rrt,int p)
{
	int setl=lrt,setr=rrt;
	int l=1,r=n,mid;
	int cts=0,ccs=0;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(p<=mid) lrt=ls[lrt],rrt=ls[rrt],r=mid;
		else
		{
			cts+=ct[ls[rrt]]-ct[ls[lrt]];
			lrt=rs[lrt],rrt=rs[rrt];
			l=mid+1;
		}
	}
	if(cts==0) return -1;
	l=1,r=n;lrt=setl;rrt=setr;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(p<=mid) lrt=ls[lrt],rrt=ls[rrt],r=mid;
		else
		{
			if(ccs+ct[ls[rrt]]-ct[ls[lrt]]<cts)
			{
				ccs+=ct[ls[rrt]]-ct[ls[lrt]];
				lrt=rs[lrt],rrt=rs[rrt],l=mid+1;
			}
			else
			{
				lrt=ls[lrt],rrt=ls[rrt],r=mid;
			}
		}
	}
	return rid[l];
}
int update(int prt,int p)
{
	int nrt=++ndcnt,l=1,r=n,mid;ct[nrt]=ct[prt]+1;
	int setrt=nrt;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(p<=mid)
		{
			rs[nrt]=rs[prt];ls[nrt]=++ndcnt;
			nrt=ls[nrt];prt=ls[prt];r=mid;
		}
		else
		{
			ls[nrt]=ls[prt];rs[nrt]=++ndcnt;
			nrt=rs[nrt];prt=rs[prt];l=mid+1;
		}
		ct[nrt]=ct[prt]+1;
	}
	return setrt;
}
void initPst(int n)
{
	for(int i=1;i<=n;i++) nd[i]=(Node){a[i],i};
	std::sort(nd+1,nd+1+n);
	for(int i=1;i<=n;i++)
	{
		rid[i]=nd[i].id;
		nd[i].v=i;
	}
	std::sort(nd+1,nd+1+n,cmp);
	for(int i=1;i<=n;i++)
		rot[i]=update(rot[i-1],nd[i].v);
}
*/
inline int findmid(int pl,int l,int r,int p)
{
	int mid,np;r++;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		np=getpos(pl,mid);
		if(np!=p) r=mid;
		else l=mid;
	}
	return l;
}
long long solve(int len,int n)
{
	long long ans=0,res;
	int p,last=0,gmax,nxt;
	while(last+len<=n)
	{
		p=getpos(last+1,last+len);
		nxt=findmid(last+1,last+len,Min(p+len-1,n),p);
//			nxt=getpos(last+1,Min(p+len-1,n))-1;
//			if(nxt<p) nxt=Min(p+len-1,n);
//		nxt=check(rot[last+len],rot[Min(p+len-1,n)],nd[p].v);
//		if(nxt<p) nxt=Min(p+len-1,n);
		gmax=getmax(last+1,nxt);
		res=(long long)gmax*a[p];
		if(res>ans)
		{
			ans=res;
//			printf("upd %lld*%lld last%d\n",a[p],gmax,last);
		}
//		ans=Max(ans,res);
		last=nxt-len+1;
//		printf("last=%d\n",last);
	}
	return ans;
}
long long solve2(int p,int n)
{
//	if(p%20==0) printf("solve%d\n",p);
	long long ans=0;
	for(int i=1;i<=n-p+1;i++)
	{
		long long mn=a[i],mx=a[i];
		for(int j=i;j<=i+p-1;j++)
		{
			mn=Min(mn,a[j]);
			mx=Max(mx,a[j]);
		}
		if(mn*mx>ans)
		{
			ans=mn*mx;
//			printf("upd %lld*%lld from %d-%d\n",mn,mx,i,i+p-1);
		}
//		ans=Max(ans,mn*mx);
	}
	return ans;
}
int main()
{
//	int c1=clock();
//	long long x=0;
	freopen("p1564.in","r",stdin);
//	freopen("p1564.out","w",stdout);
	n=RD();
	for(int i=1;i<=n;i++) a[i]=RD();
//	initPst(n);
//	initFollow(n);
	initST(n);
	
	for(long long i=1;i<=n;i++)
	{
/*		if(i<=20)
		{
			printf("time(%lld): %d\n",i,clock()-c1);
			c1=clock();
		}
*/
		long long ans;
//		if(i>3)
			ans=solve(i,n);
//		else ans=solve2(i,n);
//		x^=ans;
		printf("%lld\n",ans);
//		printf("%lld %lld\n",i,ans);
//		std::cout<<ans<<std::endl;
	}
//	printf("%lld",x);
//	printf("time %d\n",clock()-c1);
}