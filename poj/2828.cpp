#include <cstdio>
//#include <ctime>
#define N 200005
#define SZ (1<<20)
char s__[SZ],*s_s,*s_t;
//FILE *fout;
inline char gchar()
{
	if(s_s==s_t) s_s=s__,s_t=s_s+fread(s__,1,SZ-5,stdin);
	if(s_s==s_t) return 3;
	return *s_s++;
}
inline void pc(char c) {
	static const int BUF=10000000;
	static char buf[BUF], *bg=buf, *ed=buf+BUF;
	if(c) *bg++=c;
	if(bg==ed || !c) fwrite(buf, 1, bg-buf, stdout), bg=buf;
}
inline void pn(int x) {
	if(x<0) pc('-'), x=-x;
	if(x==0) pc('0');
	else {
		static int st[20], *top;
		for(top=st; x; *++top=x%10, x/=10);
		for(; top!=st; pc('0'+*top--));
	}
}
inline int RD()
{
	int res;
	char cr;
	while( ((cr=gchar())<'0' || cr>'9') && cr!=3);
	if(cr==3) return 0;
	res=cr-'0';
	while( (cr=gchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
inline int getrand()
{
	static int x0=681727,x1=22991,a1=498323,mo=1000000007;
	return x0=(x0*x1+a1)%mo;
}
struct Node{
	int w,val,sz;
	Node* son[2];
	int cmp(int p){return val==p? -1: val<p;}
	void maintain(){sz=son[0]->sz+son[1]->sz+1;}
}_sc[N],*root,*null;
Node *_sccnt;
int now;
inline Node* newNode(){return _sccnt++;}
inline void rotate(Node* &o,int d)
{
	Node* k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void insert(Node* &o,int pos,int v)
{
	if(o==null)
	{
		o=newNode();
		o->son[0]=o->son[1]=null;
		o->w=getrand();
		o->val=v;
		o->sz=1;
	}
	else
	{
		int d= o->son[0]->sz;
		if(pos<=d)
		{
			insert(o->son[0],pos,v);
			o->maintain();
//			if(now%7==0)
				if(o->son[0]->w > o->w) rotate(o,1);
		}
		else
		{
			insert(o->son[1],pos-d-1,v);
			o->maintain();
//			if(now%7==0)
				if(o->son[1]->w > o->w) rotate(o,0);
		}
	}
}

void print(Node *o)
{
	if(o==null) return;
	print(o->son[0]);
//	fprintf(fout,"%d ",o->val);
	pn(o->val);pc(' ');
	print(o->son[1]);
}
int main()
{
//	int c1=clock();
//	freopen("p2828.in","r",stdin);
//	fout=fopen("p2828.out","w");
	int n;
	while(n=RD())
	{
		_sccnt=_sc;null=new Node();root=null;
		for(int i=1,pi,vi;i<=n;i++)
		{
			++now;
//			printf("now%d\n",i);
			pi=RD();vi=RD();
			insert(root,pi,vi);
		}
		print(root);
		pc('\n');
//		printf("time%d\n",clock()-c1);
	}
	pc(0);
}