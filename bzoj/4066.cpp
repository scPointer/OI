#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 200005
#define dMin(a,b) ((a)>(b)?(a)=(b):0)
#define dMax(a,b) ((a)<(b)?(a)=(b):0)
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define inside(a,b,c) (a<=b && b<=c)
int D,ndcnt,root,ans;
const int DS=2;
struct Node{
	int mn[2],mx[2],d[2],son[2],wi,sw;
	inline bool operator <(const Node& oth)const{return d[D]<oth.d[D];}
}nd[N];
inline int newNode(int x,int y,int wi)
{
	Node& p=nd[++ndcnt];
	p.mn[0]=p.mx[0]=p.d[0]=x;
	p.mn[1]=p.mx[1]=p.d[1]=y;
	p.wi=p.sw=wi;
	return ndcnt;
}
inline void update(Node& p,Node& s)
{
	dMin(p.mn[0],s.mn[0]);
	dMin(p.mn[1],s.mn[1]);
	dMax(p.mx[0],s.mx[0]);
	dMax(p.mx[1],s.mx[1]);
	p.sw+=s.sw;
}
int build(int l,int r,int dd)
{
	D=dd;
	int mid=(l+r)>>1;
	std::nth_element(nd+l,nd+mid,nd+r+1);
	Node& p=nd[mid];
//	p.mn[0]=p.mx[0]=p.d[0];
//	p.mn[1]=p.mx[1]=p.d[1];
	if(l<mid)
		update(p,nd[p.son[0]=build(l,mid-1,dd^1)]);
	if(mid<r)
		update(p,nd[p.son[1]=build(mid+1,r,dd^1)]);
	return mid;
}
void query(Node& p,int x0,int y0,int x1,int y1,int dd)
{
	D=dd;
	if(inside(x0,p.d[0],x1)&&inside(y0,p.d[1],y1))
		ans+=p.wi;
	for(int i=0;i<2;i++)
	{
		if(!p.son[i]) continue;
		Node& s=nd[p.son[i]];
		if(s.mx[0]>=x0&&s.mn[0]<=x1&&s.mx[1]>=y0&&s.mn[1]<=y1)
			x0<=s.mn[0]&&s.mx[0]<=x1&&y0<=s.mn[1]&&s.mx[1]<=y1? (void)(ans+=s.sw): query(s,x0,y0,x1,y1,dd^1);
	}
}
void insert(Node& k,Node& rt,int nid,int dd)
{
	D=dd;
	update(rt,k);
	int cp=(rt<k);
	rt.son[cp]? insert(k,nd[rt.son[cp]],nid,dd^1): (void)(rt.son[cp]=nid);
}
void rebuild(int n)
{
	for(int i=1;i<=n;i++)
	{
		Node& p=nd[i];
		p.mx[0]=p.mn[0]=p.d[0];
		p.mx[1]=p.mn[1]=p.d[1];
		p.son[0]=p.son[1]=0;
		p.sw=p.wi;
	}
	build(1,n,0);
	root=(1+n)>>1;
}
struct Que{int tp,v1,v2,v3,v4;}q[N];
int ques,sumnd;
int main()
{
//	freopen("4066.in","r",stdin);
	int n;scanf("%d",&n);
	int tp,v1,v2,v3,v4;
	while((scanf("%d",&tp)!=EOF)&&tp!=3)
	{
		if(tp==1) scanf("%d%d%d",&v1,&v2,&v3),sumnd++;
		else scanf("%d%d%d%d",&v1,&v2,&v3,&v4);
		q[++ques]=(Que){tp,v1,v2,v3,v4};
	}
	int sz=(int)sqrt(sumnd)*17;
	for(int i=1;i<=ques;i++)
	{
		if(q[i].tp==1)
		{
			int nw=newNode(q[i].v1^ans,q[i].v2^ans,q[i].v3^ans);
//			int nw=newNode(q[i].v1,q[i].v2,q[i].v3);
			if(nw%sz==0 || nw==1) rebuild(nw);
			else insert(nd[nw],nd[root],nw,0);
		}
		else
		{
			int x0=q[i].v1^ans,y0=q[i].v2^ans,x1=q[i].v3^ans,y1=q[i].v4^ans;
//			int x0=q[i].v1,y0=q[i].v2,x1=q[i].v3,y1=q[i].v4;
			ans=0;
			if(ndcnt>0) query(nd[root],x0,y0,x1,y1,0);
			printf("%d\n",ans);
		}
	}
}