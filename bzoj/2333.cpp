#include <cstdio>
#include <algorithm>
using namespace std;
#define N  11//300005
#define Max(a,b) (a>b?a:b)
struct Que{int tp,v1,v2;}que[N];
int n,Q;
int val[N];
int dset[N*2];
int lson[N*2],rson[N*2],setcnt;
int q[N*2];
bool vis[N*2];

int pos[N],trans[N];

int dmax[N*4],prev[N*4];
int find(int p){return dset[p]!=p?dset[p]=find(dset[p]):p;}
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1;i<=n*2;i++) dset[i]=i;
	scanf("%d",&Q);
	char rd[4];
	setcnt=n;
	for(int i=1,v1,v2,fv1,fv2;i<=Q;i++)
	{
		scanf("%s",rd);
		if(rd[0]=='U')
		{
			que[i].tp=1;
			scanf("%d%d",&v1,&v2);
			que[i].v1=v1;que[i].v2=v2;
			fv1=find(v1);fv2=find(v2);
			if(fv1!=fv2)
			{
				dset[fv1]=dset[fv2]=++setcnt;
				lson[setcnt]=fv1;rson[setcnt]=fv2;
			}
		}
		else if(rd[0]=='A')
		{
			que[i].tp=1+rd[1]-'0';
			if(rd[1]=='3')
				scanf("%d",&que[i].v1);
			else
				scanf("%d%d",&que[i].v1,&que[i].v2);
		}
		else
		{
			que[i].tp=4+rd[1]-'0';
			if(rd[1]!='3')
				scanf("%d",&que[i].v1);
		}
	}
}
inline void updata(int p){dmax[p]=Max(dmax[p*2]+prev[p*2],dmax[p*2+1]+prev[p*2+1]);}
inline void pushdown(int p){if(prev[p]){dmax[p]+=prev[p];prev[p*2]+=prev[p];prev[p*2+1]+=prev[p];prev[p]=0;}}
int query(int p,int l,int r,int gl,int gr)
{
	if(gl==l && gr==r)
	{
		if(l!=r) pushdown(p);
		else dmax[p]+=prev[p];prev[p]=0;
		return dmax[p];
	}
	pushdown(p);
	int mid=(l+r)/2;
	if(gr<=mid) return query(p*2,l,mid,gl,gr);
	else if(gl>mid) return query(p*2+1,mid+1,r,gl,gr);
	int res1=query(p*2,l,mid,gl,mid);
	int res2=query(p*2+1,mid+1,r,mid+1,gr);
	return Max(res1,res2);
}
void add(int p,int l,int r,int gl,int gr,int v)
{
	if(gl==l && gr==r)
	{
		prev[p]+=v;
		return;
	}
	pushdown(p);
	int mid=(l+r)/2;
	if(gr<=mid) add(p*2,l,mid,gl,gr,v);
	else if(gl>mid) add(p*2+1,mid+1,r,gl,gr,v);
	else add(p*2,l,mid,gl,mid,v),add(p*2+1,mid+1,r,mid+1,gr,v);
	updata(p);
}
void settree(int p,int l,int r)
{
	if(l==r)
	{
		dmax[p]=val[trans[l]];
		return;
	}
	int mid=(l+r)/2;
	settree(p*2,l,mid);
	settree(p*2+1,mid+1,r);
	updata(p);
}
void setsegtree()
{
	int nds=0;
	for(int i=setcnt,l,r,p;i>=1;i--)
		if(vis[i]==0)
		{
			q[l=r=1]=i;
			while(l<=r)
			{
				p=q[l++];
				vis[p]=1;
				if(lson[p]!=0)
					q[++r]=lson[p],q[++r]=rson[p];
				if(p<=n)
				{
					++nds;
					trans[nds]=p;
					pos[p]=nds;
				}
			}
		}
	for(int i=1;i<=setcnt;i++)
		if(lson[i]==0) lson[i]=rson[i]=pos[i];
		else lson[i]=lson[lson[i]],rson[i]=rson[rson[i]];
	settree(1,1,n);
}
void solve()
{
	int nowcnt=n;
	for(int i=1;i<=setcnt;i++) dset[i]=i;
	for(int i=1,tp,v1,v2,fv1,fv2;i<=Q;i++)
	{
		tp=que[i].tp;v1=que[i].v1;v2=que[i].v2;
		if(tp==1)
		{
			fv1=find(v1);fv2=find(v2);
			if(fv1!=fv2)
				dset[fv1]=dset[fv2]=++nowcnt;
		}
		else if(tp==2)
			add(1,1,n,pos[v1],pos[v1],v2);
		else if(tp==3)
			add(1,1,n,lson[dset[v1]],rson[dset[v1]],v2);
		else if(tp==4)
			add(1,1,n,1,n,v1);
		else if(tp==5)
			printf("%d\n",query(1,1,n,pos[v1],pos[v1]));
		else if(tp==6)
			printf("%d\n",query(1,1,n,lson[dset[v1]],rson[dset[v1]]));
		else
			printf("%d\n",query(1,1,n,1,n));
	}
}
int main()
{
	init();
	setsegtree();
	solve();
}
