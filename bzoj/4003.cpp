#include <cstdio>
#define N 300005
#define Swap(a,b) {Node *t=a;a=b;b=t;}
typedef long long ll;
int fson[N],bro[N],fa[N];
int fstman[N],nxt[N],str[N];
int hei[N];
ll def[N],atk[N],tp[N],val[N];
struct Node{
	ll vi,ki,bi;
	int id;
	Node *ls,*rs;
	void calc(ll k,ll b){vi=k*vi+b;ki*=k;bi=bi*k+b;}
}nd[N];
Node *rot[N],*null;
int ans1[N],ans2[N];
inline void mark(Node* p,ll tp,ll v)
{
//	tp? p->ki*=v,p->bi*=v,p->vi*=v: p->bi+=v,p->vi+=v;//WA1
	tp? p->calc(v,0): p->calc(1,v);
}
inline Node* newnode(ll at,int id)
{
	Node& p=nd[id];
	p.id=id;p.ki=1;p.bi=0;p.vi=at;
	p.ls=p.rs=null;
	return &nd[id];
}
inline void pushdown(Node* p)
{
	if(p->ki!=1 || p->bi!=0)
	{
		Node *ps=p->ls;
//		if(ps!=null) ps->ki*=p->ki,ps->bi=ps->bi * p->ki + p->bi,ps->calc();//WA3
		if(ps!=null) ps->calc(p->ki,p->bi);
		ps=p->rs;
//		if(ps!=null) ps->ki*=p->ki,ps->bi=ps->bi * p->ki + p->bi,ps->calc();//WA3
		if(ps!=null) ps->calc(p->ki,p->bi);
		p->ki=1;p->bi=0;
	}
}
Node* merge(Node* a,Node* b)
{
	if(a==null) return b;
	if(b==null) return a;
	pushdown(a);
	pushdown(b);
	if(a->vi < b->vi)
	{
		a->rs=merge(a->rs,b);
		Swap(a->rs,a->ls)
		return a;
	}
	else
	{
		b->rs=merge(a,b->rs);
		Swap(b->ls,b->rs)
		return b;
	}
}
inline Node* pop(Node* p)
{
	pushdown(p);//WA2
	//如果不是删除根节点要记得记录并更新p->fa->(ls/rs)
	return merge(p->ls,p->rs);
}
inline Node* insert(Node* rt,Node* p){return merge(rt,p);}
void dfs(int p)
{
	hei[p]=hei[fa[p]]+1;
	for(int i=fson[p];i;i=bro[i])
	{
		dfs(i);
		rot[p]=merge(rot[p],rot[i]);
	}
	while(rot[p]!=null && rot[p]->vi<def[p])
	{
		Node& rt=*rot[p];
		ans1[p]++;
		ans2[rt.id]=hei[str[rt.id]]-hei[p];
		rot[p]=pop(rot[p]);
	}
	for(int i=fstman[p];i;i=nxt[i])
	{
		if(atk[i]>=def[p]) rot[p]=insert(rot[p],newnode(atk[i],i));
		else ans1[p]++,ans2[i]=0;
	}
	if(rot[p]!=null) mark(rot[p],tp[p],val[p]);
}
int main()
{
//	freopen("4003.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&def[i]);
	for(int i=2;i<=n;i++)
	{
		scanf("%d%lld%lld",&fa[i],&tp[i],&val[i]);
		bro[i]=fson[fa[i]];
		fson[fa[i]]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%d",&atk[i],&str[i]);
		nxt[i]=fstman[str[i]];
		fstman[str[i]]=i;
	}
	for(int i=1;i<=n;i++) rot[i]=null;
	dfs(1);
	while(rot[1]!=null)
	{
		ans2[rot[1]->id]=hei[str[rot[1]->id]];
		rot[1]=pop(rot[1]);
	}
//	int ra=0;
	for(int i=1;i<=n;i++)
//		ra^=ans1[i];
		printf("%d\n",ans1[i]);
	for(int i=1;i<=m;i++)
//		ra^=ans2[i];
		printf("%d\n",ans2[i]);
//	printf("%d\n",ra);
}