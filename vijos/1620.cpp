#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 200050
struct Point{
	int dad;
	int fson;
	int bro;
	int ct;
	int pla;
	int top;
	int light;
	int h;
}pt[MAXN];

int head[MAXN],e[MAXN*2],nt[MAXN*2],egnum;
bool vis[MAXN];

int sa[MAXN],satop;
int ssa[MAXN];

//int test_maxp;
int ans[MAXN],ansnum;
struct node{
	node():sum(0),lmax(0),rmax(0),amax(0){}
	int sum,lmax,rmax,amax;};
node nd[MAXN*4];
//struct SGT{
	int len,top,lineid;
	int sz[MAXN*4];
//	int sum[MAXN*4],lmax[MAXN*4],rmax[MAXN*4],amax[MAXN*4];
	bool changed[MAXN*4];
	void updata(int p)
	{
		nd[p].sum=nd[p*2].sum+nd[p*2+1].sum;
		nd[p].lmax=max(nd[p*2].lmax,nd[p*2].sum+nd[p*2+1].lmax);
		nd[p].rmax=max(nd[p*2+1].rmax,nd[p*2+1].sum+nd[p*2].rmax);
		nd[p].amax=max(max(nd[p*2].amax,nd[p*2+1].amax),nd[p*2].rmax+nd[p*2+1].lmax);
	}
	void push_down(int p)
	{
		if(changed[p]==0) return;
		changed[p]=0;changed[p*2]=changed[p*2+1]=1;
		int each=nd[p].sum/sz[p];
		nd[p*2].sum=sz[p*2]*each;
		nd[p*2+1].sum=sz[p*2+1]*each;
		if(each>=0)
		{
			nd[p*2].lmax=nd[p*2].rmax=nd[p*2].amax=nd[p*2].sum;
			nd[p*2+1].lmax=nd[p*2+1].rmax=nd[p*2+1].amax=nd[p*2+1].sum;
		}
		else
		{
			nd[p*2].lmax=nd[p*2].rmax=nd[p*2].amax=0;
			nd[p*2+1].lmax=nd[p*2+1].rmax=nd[p*2+1].amax=0;
		}
	}
	void SetSGT(int l,int r,int p)
	{
//		test_maxp=max(test_maxp,p);
		if(l==r)
		{
			nd[p].sum=sa[l];
			nd[p].lmax=nd[p].rmax=nd[p].amax=max(sa[l],0);
			sz[p]=1;
			return;
		}
		int mid=(l+r)/2;
		SetSGT(l,mid,p*2);
		SetSGT(mid+1,r,p*2+1);
		sz[p]=sz[p*2]+sz[p*2+1];
		updata(p);
	}
	void change(int l,int r,int p,int gl,int gr,int gv)
	{
		
		if(l==gl && r==gr)
		{
			changed[p]=1;
			nd[p].sum=gv*sz[p];//PT
			if(gv>=0)
				nd[p].lmax=nd[p].rmax=nd[p].amax=gv*sz[p];
			else
				nd[p].lmax=nd[p].rmax=nd[p].amax=0;
			return;
		}
		push_down(p);
		int mid=(l+r)/2;
		if(gl>=mid+1) change(mid+1,r,p*2+1,gl,gr,gv);
		if(gr<=mid) change(l,mid,p*2,gl,gr,gv);
		updata(p);
	}
	node merge(node a,node b)
	{
//		printf("a: %d %d %d %d\n",a.sum,a.lmax,a.rmax,a.amax);
		node c;
		c.sum=a.sum+b.sum;
		c.lmax=max(a.lmax,a.sum+b.lmax);
		c.rmax=max(b.rmax,b.sum+a.rmax);
		c.amax=max(max(a.amax,b.amax),a.rmax+b.lmax);
		return c;
	}
	node find(int l,int r,int p,int gl,int gr)
	{
//		if(p>test_maxp)
//		{
//			int stop=0;
//			stop++;
//		}
		if(l!=r && changed[p]) push_down(p);
		if(l==gl&&r==gr) return nd[p];
		int mid=(l+r)/2;
//		if(gl>=mid+1) return find(mid+1,r,p*2+1,gl,gr); WRONG
		if(gl>=mid+1) return find(mid+1,r,p*2+1,gl,gr);
//		else if(gr<=mid) return find(l,mid,p*2,gl,gr); WRONG
		else if(gr<=mid) return find(l,mid,p*2,gl,gr);
		else return merge(find(l,mid,p*2,gl,mid),find(mid+1,r,p*2+1,mid+1,gr));
	}

	
//};

//SGT tr;


int n,m;

inline void AddEdge(int p1,int p2)
{
	e[++egnum]=p2;
	nt[egnum]=head[p1];
	head[p1]=egnum;
}
void SetTree(int p)
{
	vis[p]=1;
	pt[p].ct=1;
	for(int i=head[p];i;i=nt[i])
		if(vis[e[i]]==0)
		{
			pt[e[i]].dad=p;
			pt[e[i]].h=pt[p].h+1;
			SetTree(e[i]);
			pt[p].ct+=pt[e[i]].ct;

			if(pt[p].fson==0) pt[p].fson=e[i];
			else if(pt[e[i]].ct>pt[pt[p].fson].ct)
			{
				pt[e[i]].bro=pt[p].fson;
				pt[p].fson=e[i];
			}
			else
			{
				pt[e[i]].bro=pt[pt[p].fson].bro;
				pt[pt[p].fson].bro=e[i];
			}
		}
}
void SetLine(int p)
{
	sa[++satop]=ssa[p];
	pt[p].pla=satop;
	if(pt[p].fson)
	{
		pt[pt[p].fson].top=pt[p].top;
		SetLine(pt[p].fson);
	}
	for(int i=pt[pt[p].fson].bro;i;i=pt[i].bro)
	{
		pt[i].top=i;
		SetLine(i);
	}
}
void calcu(int p1,int p2,int v)
{
	for(;pt[p1].top!=pt[p2].top;p1=pt[pt[p1].top].dad)
	{
		if(pt[pt[p1].top].h<pt[pt[p2].top].h) swap(p1,p2);
//		printf("change: %d-%d\n",pt[p1].top,p1);
		change(1,n,1,pt[pt[p1].top].pla,pt[p1].pla,v);
	}
	if(pt[p1].h<pt[p2].h) swap(p1,p2);
//	printf("change: %d-%d",p1,p2);
	change(1,n,1,pt[p2].pla,pt[p1].pla,v);
}
int findans(int p1,int p2)
{
	node u,v;
	for(;pt[p1].top!=pt[p2].top;p1=pt[pt[p1].top].dad)
	{
		if(pt[pt[p1].top].h<pt[pt[p2].top].h){swap(p1,p2);swap(u,v);}
//		printf("link %d %d\n",pt[p1].top,p1);
		u=merge(find(1,n,1,pt[pt[p1].top].pla,pt[p1].pla),u);
	}
	if(pt[p1].h<pt[p2].h){swap(p1,p2);swap(u,v);}
//	printf("link %d %d\n",p2,p1);
	u=merge(find(1,n,1,pt[p2].pla,pt[p1].pla),u);
//	printf("u: %d %d %d %d\n",u.sum,u.lmax,u.rmax,u.amax);
	swap(v.lmax,v.rmax);
	u=merge(v,u);
	return u.amax;
}
void solve()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int type,v1,v2,v3;
		scanf("%d",&type);
		if(type==2)
		{
			scanf("%d%d%d",&v1,&v2,&v3);
			calcu(v1,v2,v3);
		}
		else
		{
			scanf("%d%d",&v1,&v2);
//			printf("%d ",findans(v1,v2));
			ans[++ansnum]=findans(v1,v2);
		}
	}
	for(int i=1;i<=ansnum-1;i++)
		printf("%d ",ans[i]);
	printf("%d",ans[ansnum]);
	printf("\n");
}
int main()
{
	freopen("p1620.in","r",stdin);
	freopen("p1620.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&ssa[i]);
	for(int i=1;i<=n-1;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		AddEdge(p1,p2);
		AddEdge(p2,p1);
	}
	pt[1].h=1;
	pt[1].dad=1;
	SetTree(1);
	pt[1].top=1;
	SetLine(1);
	SetSGT(1,n,1);
//	printf("%d",test_maxp);
	solve();
	return 0;
}
