#include <cstdio>
#include <algorithm>
#define N 505
#define ls(p) (p<<1)
#define rs(p) ((p<<1)+1)
#define Min(a,b) (a<b?a:b)
#define Abs(a) ((a)<0?-(a):(a))
#define eps 1e-8
double hash[N*8];
int hcnt;
struct Segment{
	double l,r,h;
	int tp;
	bool operator<(const Segment& ot)const{return h<ot.h;}
}seg[N*2];
int segcnt;
int gethash(double p)
{
	int l=1,r=hcnt+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(p+eps<hash[mid]) r=mid;
		else l=mid;
	}
	return l;
}
int dmin[N*8],prev[N*8];
double len[N*8];
inline void update(int p){dmin[p]=Min(dmin[ls(p)]+prev[ls(p)],dmin[rs(p)]+prev[rs(p)]);}
inline void pushdown(int p)
{
	if(prev[p]!=0)
	{
		prev[ls(p)]+=prev[p];
		prev[rs(p)]+=prev[p];
		dmin[p]+=prev[p];
		prev[p]=0;
	}
}
void settree(int p,int l,int r)
{
	dmin[p]=prev[p]=0;
	if(l==r) len[p]=hash[l]-hash[l-1];
	else
	{
		int mid=(l+r)>>1;
		settree(ls(p),l,mid);
		settree(rs(p),mid+1,r);
		len[p]=len[ls(p)]+len[rs(p)];
	}
}
double add(int p,int l,int r,int gl,int gr,int v)
{
	if(l==r)
	{
		int preval=dmin[p]+prev[p];
		prev[p]+=v;
		dmin[p]+=prev[p];prev[p]=0;
		if(preval>0 && dmin[p]==0) return -len[p];
		else if(preval==0 && dmin[p]>0) return len[p];
		else return 0;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	double res=0;
	if(gr<=mid) res=add(ls(p),l,mid,gl,gr,v);
	else if(mid<gl) res=add(rs(p),mid+1,r,gl,gr,v);
	else res=add(ls(p),l,mid,gl,mid,v) + add(rs(p),mid+1,r,mid+1,gr,v);
	update(p);
	return res;
}
int main()
{
	int n;
	int T=0;
	while(~scanf("%d",&n) && n!=0)
	{
		++T;
		hcnt=segcnt=0;
		double x1,y1,x2,y2;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			hash[++hcnt]=x1;hash[++hcnt]=x2;
			seg[++segcnt]=(Segment){x1,x2,y1,1};
			seg[++segcnt]=(Segment){x1,x2,y2,-1};
		}
		std::sort(seg+1,seg+segcnt+1);
		std::sort(hash+1,hash+hcnt+1);
		settree(1,1,hcnt);
		double covered=0,ans=0;
		for(int i=1;i<=segcnt-1;i++)
		{
			covered+=add(1,1,hcnt,gethash(seg[i].l)+1,gethash(seg[i].r),seg[i].tp);
			ans+=covered*(seg[i+1].h-seg[i].h);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n",T,ans);
	}
}