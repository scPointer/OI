#include <cstdio>
#include <algorithm>
#define N 30005
#define ls(p) (p<<1)
#define rs(p) ((p<<1)+1)
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
struct Segment{
	int l,r,h;
	int tp;
	bool operator<(const Segment& ot)const{return h!=ot.h? h<ot.h: tp>ot.tp;}
	//if(h==ot.h) check "tp>ot.tp" !!!!!
}seg[N*2],segy[N*2];
int segcnt,segycnt;
int dmin[N*7],prev[N*7];
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
	if(l<r)
	{
		int mid=(l+r)>>1;
		settree(ls(p),l,mid);
		settree(rs(p),mid+1,r);
	}
}
int add(int p,int l,int r,int gl,int gr,int v)
{
	if(l==r)
	{
		int preval=dmin[p]+prev[p];
		prev[p]+=v;
		dmin[p]+=prev[p];prev[p]=0;
		if(preval>0 && dmin[p]==0) return 1;
		else if(preval==0 && dmin[p]>0) return 1;
		else return 0;
	}
	int mid=(l+r)>>1;
	int res=0;
	if(gr<=mid) res=add(ls(p),l,mid,gl,gr,v);
	else if(mid<gl) res=add(rs(p),mid+1,r,gl,gr,v);
	else res=add(ls(p),l,mid,gl,mid,v) + add(rs(p),mid+1,r,mid+1,gr,v);
	return res;
}
int main()
{
	int n;
	while(~scanf("%d",&n) && n!=0)
	{
		int ans=0;
		segcnt=0;segycnt=0;
		int x1,y1,x2,y2;
		int maxx=0,maxy=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1+=10001;y1+=10001;x2+=10001;y2+=10001;
			maxx=Max(maxx,x2);maxy=Max(maxy,y2);
			seg[++segcnt]=(Segment){x1,x2,y1,1};
			seg[++segcnt]=(Segment){x1,x2,y2,-1};
			segy[++segycnt]=(Segment){y1,y2,x1,1};
			segy[++segycnt]=(Segment){y1,y2,x2,-1};
		}
		std::sort(seg+1,seg+segcnt+1);
		settree(1,1,maxx);
		for(int i=1;i<=segcnt;i++)
			ans+=add(1,1,maxx,seg[i].l+1,seg[i].r,seg[i].tp);
			
		std::sort(segy+1,segy+segycnt+1);
		settree(1,1,maxy);
		for(int i=1;i<=segycnt;i++)
			ans+=add(1,1,maxy,segy[i].l+1,segy[i].r,segy[i].tp);
		printf("%d\n",ans);
	}
}