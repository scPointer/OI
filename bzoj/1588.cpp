#include <cstdio>
#define N 1200005
#define INF 2147483647
#define Min(a,b) (a<b?a:b)
int mrand()
{
	static int x=4973,a=54491,b=79813855,mo=1000000007;
	return x=(x*a+b)%mo;
}
struct Node *null;
struct Node
{
	Node* son[2];
	int w,r,sz;
	int cmp(int v){if(v==w) return -1;else return w<v;}
	void init(int _w){r=mrand();w=_w;son[0]=son[1]=null;sz=1;}
	void maintain(){sz=son[0]->sz+son[1]->sz+1;}
}*head,sc[N];
int cntnodes;
inline void initNode(){head=null=new Node();}
inline Node* newNode(){return &sc[++cntnodes];}
inline void rotate(Node* &p,int d)
{
	Node* k=p->son[d^1];
	p->son[d^1]=k->son[d];
	k->son[d]=p;
	p->maintain();
	k->maintain();
	p=k;
}
void insert(int w,Node* &p=head)
{
	if(p==null){p=newNode();p->init(w);}
	else
	{
		int d=p->cmp(w);
		insert(w,p->son[d]);
		if(p->son[d]->r > p->r) rotate(p,d^1);
		else p->maintain();
	}
}
int find(int w,int rank=0,Node* p=head)
{
	if(p==null) return rank;
	int d=p->cmp(w);
	if(d==-1) return -1;
	return find(w,(d? rank+p->son[0]->sz+1: rank),p->son[d]);
}
int findkth(int kth,Node* p=head)
{
	if(p->son[0]->sz+1 == kth) return p->w;
	else if(p->son[0]->sz >= kth) return findkth(kth,p->son[0]);
	else return findkth(kth- p->son[0]->sz -1,p->son[1]);
}
int main()
{
	initNode();
	int n,val,kth,le,ri,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		if((scanf("%d",&val))==EOF) val=0;
		if(head==null){ans+=val;insert(val);continue;}
		if((kth=find(val))!=-1)
		{
			le= kth>0? val-findkth(kth): INF;
			ri= kth<cntnodes? findkth(kth+1)-val: INF;
			ans+=Min(le,ri);
			insert(val);
		}
	}
	printf("%d\n",ans);
	return 0;
}
