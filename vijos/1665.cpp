#include <cstdio>
#include <algorithm>
using namespace std;
#define NODE 21110000
#define N 100005
#define lowbit(x) ((x)&(-x))
inline int RD(int& res)
{
	static char cr;
	while((cr=getchar())<'0' || cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int l[NODE],r[NODE],c[NODE],sgt,root[N];
int haj[N];
int pre[N],h[N],precnt;

int od[N][4];
int n,m;
void preHash()
{
	sort(pre+1,pre+1+precnt);
	int i=0,p=1;
	while(p<=precnt)
	{
		while(p<=precnt && pre[p]==pre[i]) p++;
		if(p>precnt) break;
		pre[(i++)+1]=pre[p];
	}
	precnt=i;
}
int gethash(int p)
{
	int l=1,r=precnt,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(pre[mid]<p) l=mid+1;
		else r=mid;
	}
	return r;
}
int setTree(int ll,int rr)
{
	int rt=++sgt;c[rt]=0;
	if(ll==rr) return rt;
	l[rt]=setTree(ll,(ll+rr)>>1);
	r[rt]=setTree(((ll+rr)>>1)+1,rr);
//	c[rt]=c[l[rt]]+c[r[rt]];
	return rt;
}
int updata(int prt,int v,int nb)
{
	int rt=++sgt,ll=1,rr=precnt,mid;c[rt]=c[prt]+nb;
	int setrt=rt;
	while(ll<rr)
	{
		mid=(ll+rr)>>1;
		if(v<=mid)
		{
			r[rt]=r[prt];l[rt]=++sgt;
			rt=l[rt];prt=l[prt];rr=mid;
		}
		else
		{
			l[rt]=l[prt];r[rt]=++sgt;
			rt=r[rt];prt=r[prt];ll=mid+1;
		}
		c[rt]=c[prt]+nb;
	}
	return setrt;
}
void setTreeInTree()
{
	for(int i=1;i<=n;i++)
	{
		h[i]=gethash(haj[i]);
		for(int j=i;j<=n;j+=lowbit(j))
		{
			if(!root[j]) root[j]=updata(root[0],h[i],1);
			else root[j]=updata(root[j],h[i],1);
		}
	}
}
void change(int p,int v)
{
	int hv=gethash(v),oldval=h[p];
	haj[p]=v;h[p]=gethash(haj[p]);
	for(int i=p;i<=n;i+=lowbit(i))
	{root[i]=updata(root[i],oldval,-1);root[i]=updata(root[i],hv,1);}
}
void query(int ls,int rs,int kth)
{
	int ll=1,rr=precnt,mid,lsum,rsum;
	int lt[20]={0},ltot=0,rt[20]={0},rtot=0;
	for(int i=ls;i>0;i-=lowbit(i))
		lt[++ltot]=root[i];
	for(int i=rs;i>0;i-=lowbit(i))
		rt[++rtot]=root[i];
	while(ll<rr)
	{
		mid=(ll+rr)>>1;
		lsum=rsum=0;
		for(int i=1;i<=ltot;i++)
			lsum+=c[l[lt[i]]];
		for(int i=1;i<=rtot;i++)
			rsum+=c[l[rt[i]]];
		if(rsum-lsum>=kth)
		{
			for(int i=1;i<=ltot;i++)
				lt[i]=l[lt[i]];
			for(int i=1;i<=rtot;i++)
				rt[i]=l[rt[i]];
			rr=mid;
		}
		else
		{
			kth-=rsum-lsum;
			for(int i=1;i<=ltot;i++)
				lt[i]=r[lt[i]];
			for(int i=1;i<=rtot;i++)
				rt[i]=r[rt[i]];
			ll=mid+1;
		}
	}
	printf("%d\n",pre[ll]);
}
int main()
{
	RD(n);RD(m);
	for(int i=1;i<=n;i++) pre[++precnt]=RD(haj[i]);
	for(int i=1;i<=m;i++)
	{
		static char cr;
		while((cr=getchar())!='C' && cr!='Q');
		if(cr=='Q'){od[i][0]=1;RD(od[i][1]);RD(od[i][2]);RD(od[i][3]);}
		else{od[i][0]=2;RD(od[i][1]);pre[++precnt]=RD(od[i][2]);}
	}
	
	preHash();
	root[0]=setTree(1,precnt);
	setTreeInTree();
	for(int i=1;i<=m;i++)
		if(od[i][0]==1) query(od[i][1]-1,od[i][2],od[i][3]);
		else change(od[i][1],od[i][2]);
	return 0;
}
