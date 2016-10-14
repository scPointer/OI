#include <cstdio>
#include <cmath>
#include <algorithm>
//using namespace std;
#define N 32005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
inline int RD()
{
	static char cr;
	static int res,sign;
/*	while( ((cr=getchar())<'0' || cr>'9') && cr!='-');
	cr=='-'? sign=-1,res=0: sign=1,res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
	res=res*10+cr-'0';
*/
	scanf("%d",&res);
	return res;
}
struct Node{
	long long x,y,r;
	bool inclu(Node& o)
	{return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)<(r-o.r)*(r-o.r);}
	bool incircle(long long _x,long long _y)
	{return (x-_x)*(x-_x)+(y-_y)*(y-_y)<r*r;}
}nd[N];
bool cmp(Node a,Node b){return a.r>b.r;}
int fson[N],bro[N],ndcnt;

void addNode(int o,int p)
{
	for(int i=fson[p];i;i=bro[i])
		if(nd[i].inclu(nd[o]))
		{
			addNode(o,i);
			return;
		}
//	nd[ndcnt++]=rnode[o];
	bro[o]=fson[p];
	fson[p]=o;
}
int find(long long x,long long y,int p)
{
	for(int i=fson[p];i;i=bro[i])
		if(nd[i].incircle(x,y))
			return find(x,y,i);
	return p;
}
int timetip,odr[N*2],rmq[N],le[N],ri[N],h[N];
int st[N*2][16],ptr[N*2][16],lg2[N*4];
void setTree(int p)
{
	le[p]=++timetip;
	odr[timetip]=p;
	rmq[timetip]=h[p];
	
	for(int i=fson[p];i;i=bro[i])
	{
		h[i]=h[p]+1;
		setTree(i);
		if(bro[i]!=0)
		{
			++timetip;
			odr[timetip]=p;
			rmq[timetip]=h[p];
		}
	}
	if(fson[p]!=0) ri[p]=++timetip;
	else ri[p]=timetip;
	odr[timetip]=p;
	rmq[timetip]=h[p];
}
int lca(int p1,int p2)
{
	if(p1==p2) return p1;
	if(le[p1]<le[p2] && ri[p2]<ri[p1]) return p1;
	if(le[p2]<le[p1] && ri[p1]<ri[p2]) return p2;
	int l=Min(le[p1],le[p2]);
	int r=Max(le[p1],le[p2]);
	int len=lg2[r-l+1]-1;
	return st[l][len]<st[r-(1<<len)+1][len]? ptr[l][len]: ptr[r-(1<<len)+1][len];
}
int main()
{
//	freopen("p1989.in","r",stdin);
	int root,n=RD();
	nd[ root=ndcnt++ ]= (Node){0,0,-1};
	for(int i=1,x,y,r;i<=n;i++)
	{
		x=RD();y=RD();r=RD();
		nd[i]=(Node){x,y,r};
	}
 	std::sort(nd+1,nd+1+n,cmp);
	for(int i=1;i<=n;i++)
		addNode(i,root);
	setTree(root);
	
	for(int i=1,j=1;j<n*2;i++,j<<=1)
		for(int k=j;k<j*2;k++)
			lg2[k]=i;
	for(int i=1;i<=n*2;i++) st[i][0]=rmq[i],ptr[i][0]=odr[i];
	for(int i=1,j=1;j<n*2;i++,j<<=1)
		for(int k=1,nxt;k<=n*2;k++)
		{
			nxt=k+(1<<(i-1));
			if(nxt <=n*2)
			{
				st[k][i]=Min(st[k][i-1],st[nxt][i-1]);
				ptr[k][i]=st[k][i-1]<st[nxt][i-1]? ptr[k][i-1]: ptr[nxt][i-1];
			}
		}
	int x1,y1,x2,y2,p1,p2,p3;
	for(int Q=RD();Q;Q--)
	{
		x1=RD();y1=RD();x2=RD();y2=RD();
		p1=find(x1,y1,root);
		p2=find(x2,y2,root);
		p3=lca(p1,p2);
//		printf("lca: %d\n",p3);
		printf("%d\n",h[p1]+h[p2]-h[p3]*2);
	}
}
