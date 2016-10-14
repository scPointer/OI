//1-indexed
#define N 
#define Swap(a,b) {_temp=a;a=b;b=_temp;}
namespace lct{

int son[N][2],fa[N];
bool rev[N];
int stk[N];
int _temp;
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return son[fa[p]][0]!=p && son[fa[p]][1]!=p;}
inline void sets(int d,int p,int f){son[f][d]=p;fa[p]=f;}
inline void update(int p){}
inline void pushdown(int p)
{
    if(rev[p])
    {
        Swap(son[p][0],son[p][1])
        if(son[p][0]!=0) rev[son[p][0]]^=1;
        if(son[p][1]!=0) rev[son[p][1]]^=1;
        rev[p]=0;
    }
}
void rotate(int p)
{
    static int d,Fa;
    d=getd(p);Fa=fa[p];
    isrt(Fa)? (void)(fa[p]=fa[Fa]): sets(getd(Fa),p,fa[Fa]);
    sets(d,son[p][d^1],Fa);
    sets(d^1,Fa,p);
    update(Fa);
}
void splay(int p)
{
    static int top,pt;
    top=0;
    for(pt=p;!isrt(pt);pt=fa[pt]) stk[++top]=pt;
    stk[++top]=pt;
    for(pt=top;pt>=1;pt--) pushdown(stk[pt]);
    while(!isrt(p))
    {
        if(!isrt(fa[p]))
            getd(p)==getd(fa[p])?rotate(fa[p]):rotate(p);
        rotate(p);
    }
    update(p);
}
int access(int p)
{
    int y=0;
    while(p!=0)
    {
        splay(p);
        son[p][1]=y;
        y=p;
        p=fa[p];
    }
    return y;
}
void mkroot(int p)
{
    int res=access(p);
    rev[res]^=1;
    splay(p);
}
void link(int x,int y)
{
    mkroot(x);
    fa[x]=y;
    access(x);
}
void split(int x,int y)
{
    mkroot(x);
    access(y);
    splay(y);
}
void cut(int x,int y)
{
    split(x,y);
    fa[x]=0;
    son[y][getd(x)]=0;
}
bool find(int& goal,int p)
{
    if(p==goal) return 1;
    if(p==0) return 0;
    return find(goal,son[p][0]);
}

}