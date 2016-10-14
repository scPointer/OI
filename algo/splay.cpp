#define N 
#define ND 
#define gp son[son[root][1]][0]
#define Swap(a,b) {_temp=a;a=b;b=_temp;}
namespace splay{

int sc[N];//used to build() multiple nodes
int son[ND][2],fa[ND];
int cnt[ND];
int val[ND];
//val[] store info of nodes,it can be explaced struct{}
bool rev[ND];
int stk[ND],tops;
int nds,root;
int _temp;
inline void addNode(int p,int pval){cnt[p]=1;val[p]=pval;}
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return fa[p]==0;}
inline void sets(int d,int p,int f){son[f][d]=p;fa[p]=f;}
inline void update(int p){if(p!=0) cnt[p]=cnt[son[p][0]]+cnt[son[p][1]]+1;}
//update() can be changed
inline void pushdown(int p)
{
    if(rev[p])
    {
        Swap(son[p][0],son[p][1])
        rev[p]=0;
        if(son[p][0]!=0) rev[son[p][0]]^=1;
        if(son[p][1]!=0) rev[son[p][1]]^=1;
    }
}
void rotate(int p)
{
    int d=getd(p);
    int Fa=fa[p];
    /*isrt(Fa)?(void)(fa[p]=fa[Fa]): */sets(getd(Fa),p,fa[Fa]);
    sets(d,son[p][d^1],Fa);
    sets(d^1,Fa,p);
    update(Fa);
//  updata(p);
}
void splay(int p,int goalfa)
{
    if(p==0) return;
    tops=0;
    for(int k=p;k!=goalfa;k=fa[k]) stk[++tops]=k;
    for(int k=tops;k>=1;k--) pushdown(stk[k]);
    for(int k=1;k<=tops;k++) update(stk[k]);
    while(fa[p]!=goalfa)
    {
        if(fa[fa[p]]!=goalfa)
            getd(p)==getd(fa[p])? rotate(fa[p]): rotate(p);
        rotate(p);
    }
    update(p);
    if(goalfa==0) root=p;
}
int findkth(int pos,int p)
{
    if(p==0) return 0;
    pushdown(p);
    if(cnt[son[p][0]]>=pos) return findkth(pos,son[p][0]);
    else if(cnt[son[p][0]]+1>=pos)
        return p;
    else return findkth(pos-cnt[son[p][0]]-1,son[p][1]);
}
int find(int pos)
{
    int p=findkth(pos,root);
    return val[p];
}
void build(int d,int Fa,int l,int r)
{
    int mid=(l+r)/2,newnd=++nds;
    addNode(newnd,sc[mid]);
    sets(d,newnd,Fa);
    if(l<mid)  build(0,newnd,l,mid-1);
    if(mid<r) build(1,newnd,mid+1,r);
    update(newnd);
}
void insert(int ptr,int pfst,int plen)
{
    splay(findkth(ptr,root),0);
    splay(findkth(ptr+1,root),root);
    build(0,son[root][1],pfst,pfst+plen-1);
    update(son[root][1]);
    update(root);
}
void evert(int ptr,int slen)
{
    splay(findkth(ptr,root),0);
    splay(findkth(ptr+slen+1,root),root);
    rev[gp]^=1;
}
void remove(int ptr,int slen)
{
    splay(findkth(ptr,root),0);
    splay(findkth(ptr+slen+1,root),root);
    gp=0;
    update(son[root][1]);
    update(root);
}
void init()
{
	addNode(++nds,-1);sets(0,nds,0);root=nds;
    addNode(++nds,-1);sets(1,nds,root);update(root);
}

}
