#include <cstdio>
#include <algorithm>
#define N 100005
#define M 100005
#define ND 8000005
#define lowbit(x) (x&(-x))
int hash[M],hcnt,pre[M],pcnt;
struct Que{int tp,l,r,k;}q[N];
int sc[N],hsc[N];
void setHash()
{
	std::sort(pre+1,pre+1+pcnt);pre[0]=-1;
	for(int i=1;i<=pcnt;i++)
		if(pre[i]!=pre[i-1])
			hash[++hcnt]=pre[i];
	hash[hcnt+1]=(int)(1e9);hash[0]=-1;
}
inline int gethash(int p)
{
	static int l,r,mid;
	l=0,r=hcnt+1;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(hash[mid]>p) r=mid;
		else l=mid;
	}
	return l;
}
inline int getpre(int p)
{
	int res=gethash(p);
	while(hash[res]>=p) res--;
	return res;
}
inline int getflo(int p)
{
	int res=gethash(p);
	while(hash[res]<=p) res++;
	return res;
}
int ls[ND],rs[ND],c[ND],tcnt;
int rot[N];
int initTree(int l,int r)
{
	int nd=++tcnt;c[nd]=0;
	if(l==r) return nd;
	ls[nd]=initTree(l,(l+r)/2);
	rs[nd]=initTree((l+r)/2+1,r);
	return nd;
}
int update(int prt,int p,int nb)
{
	int nrt=(++tcnt)%ND,l=1,r=hcnt,mid;c[nrt]=c[prt]+nb;
	int setrt=nrt;
	while(l<r)
	{
		mid=(l+r)/2;
		if(p>mid)
		{
			ls[nrt]=ls[prt];rs[nrt]=(++tcnt)%ND;
			nrt=rs[nrt];prt=rs[prt];
			l=mid+1;
		}
		else
		{
			rs[nrt]=rs[prt];ls[nrt]=(++tcnt)%ND;
			nrt=ls[nrt];prt=ls[prt];
			r=mid;
		}
		c[nrt]=c[prt]+nb;
	}
	return setrt;
}
void setTree(int n)
{
	for(int i=1;i<=n;i++) sc[i]=0;
	for(int i=1;i<=n;i++)
		if(sc[i+lowbit(i)]==0) sc[i+lowbit(i)]=i;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=lowbit(j))
			if(sc[j]<i) rot[j]=update(rot[j],hsc[i],1);
			else if(sc[j]==i) rot[j]=rot[i];
}
int qa[22],atop,qb[22],btop;
int tl,tr;
inline void init(){
	atop=0;for(int i=tl;i>0;i-=lowbit(i)) qa[++atop]=rot[i];
	btop=0;for(int i=tr;i>0;i-=lowbit(i)) qb[++btop]=rot[i];
}
inline void goleft(){
	for(int i=1;i<=atop;i++) qa[i]=ls[qa[i]];
	for(int i=1;i<=btop;i++) qb[i]=ls[qb[i]];
}
inline void goright(){
	for(int i=1;i<=atop;i++) qa[i]=rs[qa[i]];
	for(int i=1;i<=btop;i++) qb[i]=rs[qb[i]];	
}
inline int getleft(){
	static int res; res=0;
 	for(int i=1;i<=atop;i++) res-=c[ls[qa[i]]];
	for(int i=1;i<=btop;i++) res+=c[ls[qb[i]]];
	return res;
}
inline int getthis(){
	static int res; res=0;
	for(int i=1;i<=atop;i++) res-=c[qa[i]];
	for(int i=1;i<=btop;i++) res+=c[qb[i]];
	return res;
}
int findrank(int tr,int tl,int k)
{
	init();
	int l=1,r=hcnt,mid,res=0;
	while(l<r)
	{
		mid=(l+r)/2;
		if(k<=mid) goleft(),r=mid;
		else{
			res+=getleft();
			goright();
			l=mid+1;
		}
	}
	return res+1;//wa*2: "return res+getthis();"  Excuse me?
}
int findkth(int tr,int tl,int k)
{
	init();
	int l=1,r=hcnt,mid,res;
	while(l<r)//NOT l<=r
	{
		mid=(l+r)/2;
		if((res=getleft())>=k) goleft(),r=mid;
		else goright(),l=mid+1,k-=res;
	}
	return hash[l];
}
int findpre(int tr,int tl,int k)
{
	init();
	int l=1,r=hcnt,mid;
	int cnts=0,cks=0,res=0;
	while(l<r)
	{
		mid=(l+r)/2;
		if(k<=mid) goleft(),r=mid;
		else{cnts+=getleft();goright();l=mid+1;}
	}
	cnts+=getthis();
	l=1,r=hcnt;init();
	while(l<r)
	{
		mid=(l+r)/2;
		if(k<=mid) goleft(),r=mid;
		else
		{
			res=getleft();
			if(cks+res==cnts) goleft(),r=mid;
			else goright(),l=mid+1,cks+=res;
		}
	}
	return hash[l];
}
int findflo(int tr,int tl,int k)
{
	init();
	int l=1,r=hcnt,mid;
	int cnts=0,cks=0,res=0;
	while(l<r)
	{
		mid=(l+r)/2;
		if(k<=mid) goleft(),r=mid;
		else{cnts+=getleft();goright();l=mid+1;}
	}
	l=1,r=hcnt;init();
	while(l<r)
	{
		mid=(l+r)/2;
		if(k<=mid)
		{
			res=getleft();
			if(cks+res==cnts) goright(),l=mid+1,cks+=res;
			else goleft(),r=mid;
		}
		else {cks+=getleft();goright();l=mid+1;}
		//wa*3: goright(),cks+=getleft(),l=mid+1;
	}
	return hash[l];
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&sc[i]);
		pre[++pcnt]=sc[i];
	}
	for(int i=1,tp,v1,v2,v3;i<=m;i++)
	{
		scanf("%d%d%d",&tp,&v1,&v2);
		if(tp!=3) scanf("%d",&v3);
		else pre[++pcnt]=v2;
		q[i]=(Que){tp,v1,v2,v3};
	}
	setHash();
	for(int i=1;i<=n;i++) hsc[i]=gethash(sc[i]);
	rot[0]=initTree(1,hcnt);
//	for(int i=1;i<=n;i++) rot[i]=rot[0];
	setTree(n);
	
	for(int i=1,tp,ll,rr,k;i<=m;i++)
	{
		tp=q[i].tp;ll=q[i].l;rr=q[i].r;k=q[i].k;
		tl=ll-1;tr=rr;
		if(tp==3){
			for(int i=ll;i<=hcnt;i+=lowbit(i))
			{
				rot[i]=update(rot[i],hsc[ll],-1);
				//wa*1: rot[i]=update(rot[i],hsc[i],-1);
				rot[i]=update(rot[i],gethash(rr),1);
			}
			hsc[ll]=gethash(rr);
		}
		else if(tp==1) printf("%d\n",findrank(rr,ll-1,gethash(k)));
		else if(tp==2) printf("%d\n",findkth(rr,ll-1,k));
		else if(tp==4) printf("%d\n",findpre(rr,ll-1,getpre(k)));
		else printf("%d\n",findflo(rr,ll-1,getflo(k)));
	}
}
