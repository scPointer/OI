#include <cstdio>
#define N 100005
#define ls (p<<1)
#define rs (p<<1)+1
int fa[N],bro[N],head[N];
int sz[N],pson[N],top[N],h[N];
int pos[N],last[N],timetip;
void dfs1(int p)
{
	h[p]=h[fa[p]]+1;
	sz[p]=1;
	for(int i=head[p];i;i=bro[i])
	{
		dfs1(i);
		sz[p]+=sz[i];
		if(sz[i]>sz[pson[p]]) pson[p]=i;
	}
}
void dfs2(int p,int tp)
{
	pos[p]=++timetip;
	top[p]=tp;
	if(pson[p]) dfs2(pson[p],tp);
	for(int i=head[p];i;i=bro[i])
		if(i!=pson[p])
			dfs2(i,i);
	last[p]=timetip;
}
int sum[N*4],prev[N*4],size[N*4];
inline void pushdown(int p)
{
	if(prev[p]!=-1)
	{
		prev[ls]=prev[rs]=prev[p];
		sum[ls]=size[ls]*prev[p];
		sum[rs]=size[rs]*prev[p];
		prev[p]=-1;
	}
}
inline void update(int p){sum[p]=sum[ls]+sum[rs];}
int query(int p,int l,int r,int gl,int gr)
{
	if(l==gl && r==gr)
	{
		if(l!=r) pushdown(p);
		return sum[p];
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(gr<=mid) return query(ls,l,mid,gl,gr);
	else if(mid+1<=gl) return query(rs,mid+1,r,gl,gr);
	else return query(ls,l,mid,gl,mid) + query(rs,mid+1,r,mid+1,gr);
}
void cover(int p,int l,int r,int gl,int gr,int v)
{
	if(l==gl && r==gr)
	{
		sum[p]=size[p]*v;
		prev[p]=v;
		return;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(gr<=mid) cover(ls,l,mid,gl,gr,v);
	else if(mid+1<=gl) cover(rs,mid+1,r,gl,gr,v);
	else cover(ls,l,mid,gl,mid,v) , cover(rs,mid+1,r,mid+1,gr,v);
	update(p);
}
void setTree(int p,int l,int r)
{
	prev[p]=-1;
	size[p]=r-l+1;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		setTree(ls,l,mid);
		setTree(rs,mid+1,r);
	}
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);fa[i]++;
		bro[i]=head[fa[i]];
		head[fa[i]]=i;
	}
	dfs1(1);dfs2(1,1);
	setTree(1,1,n);
	char odr[11];
	int m; scanf("%d",&m);
	for(int i=1,p;i<=m;i++)
	{
		scanf("%s%d",odr,&p); p++;
		if(odr[0]=='i')
		{
			int res=0;
			for(int tp=p;tp;tp=fa[top[tp]])
			{
				res+=pos[tp]-pos[top[tp]]+1- query(1,1,n,pos[top[tp]],pos[tp]);
				cover(1,1,n,pos[top[tp]],pos[tp],1);
			}
			printf("%d\n",res);
		}
		else
		{
			printf("%d\n",query(1,1,n,pos[p],last[p]));
			cover(1,1,n,pos[p],last[p],0);
		}
	}
}