#include <cstdio>
#include <algorithm>
#define getmid() std::nth_element(nd+l,nd+mid,nd+r+1,cmp)
#define N 800005
#define dMin(a,b) ((a)>(b)?(a)=(b):0)
#define dMax(a,b) ((a)<(b)?(a)=(b):0)
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define INF 1000000007
struct Node{
    int mn[2],mx[2],d[2],son[2];
}nd[N];
struct Point{int x,y;};
int root,ndcnt,D;
int ans;
inline bool cmp(Node a,Node b){return a.d[D]!=b.d[D]? a.d[D]<b.d[D]: a.d[D^1]<b.d[D^1];}
inline void update(Node& p,Node& s)
{
    dMin(p.mn[0],s.mn[0]);
    dMin(p.mn[1],s.mn[1]);
    dMax(p.mx[0],s.mx[0]);
    dMax(p.mx[1],s.mx[1]);
}
inline int newnode(Point p)
{
    Node& nw=nd[++ndcnt];//nd[0] is used as null
    nw.mn[0]=nw.mx[0]=nw.d[0]=p.x;
    nw.mn[1]=nw.mx[1]=nw.d[1]=p.y;
    return ndcnt;
}
int build(int l,int r,int dd)
{
    D=dd;
    int mid=(l+r)>>1;
    getmid();
    Node& p=nd[mid];
    if(l<mid)
        update(p,nd[p.son[0]=build(l,mid-1,dd^1)]);
    if(mid<r)
        update(p,nd[p.son[1]=build(mid+1,r,dd^1)]);
    return mid;
}
void insert(Node& nw,Node& rt,int nid,int dd)
{
    D=dd;
    update(rt,nw);
    int cp=cmp(rt,nw);
    rt.son[cp]? insert(nw,nd[rt.son[cp]],nid,dd^1): (void)(rt.son[cp]=nid);
}
inline int getd(Node& k,Point& p)
{
    int res=0;
    res+=Max(k.mn[0]-p.x,0);
    res+=Max(p.x-k.mx[0],0);
    res+=Max(k.mn[1]-p.y,0);
    res+=Max(p.y-k.mx[1],0);
    return res;
}
void query(Node& k,Point& p)
{
    int dn=abs(p.x-k.d[0])+abs(p.y-k.d[1]);
    dMin(ans,dn);
	int ds[2];
    ds[0]= k.son[0]? getd(nd[k.son[0]],p): INF;
    ds[1]= k.son[1]? getd(nd[k.son[1]],p): INF;
    bool dk=(ds[0]>ds[1]);
    if(ds[dk]<ans) query(nd[k.son[dk]],p);
    if(ds[dk^1]<ans) query(nd[k.son[dk^1]],p);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,px,py;i<=n;i++)
    {
        scanf("%d%d",&px,&py);
        newnode((Point){px,py});
    }
    root=(ndcnt+1)>>1;
    build(1,ndcnt,0);
    for(int i=1,tp,px,py;i<=m;i++)
    {
        scanf("%d%d%d",&tp,&px,&py);
        Point p=(Point){px,py};
        if(tp==1)
        {
            int nw=newnode(p);
            insert(nd[nw],nd[root],nw,0);
        }
        else
        {
            ans=INF;
            query(nd[root],p);
            printf("%d\n",ans);
        }
    }
}