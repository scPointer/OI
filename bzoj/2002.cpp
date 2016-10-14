#include <cstdio>
#define N 200005
int fa[N],son[N][2],sz[N];
int n;
inline int RD(){static int res;scanf("%d",&res);return res;}
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return son[fa[p]][0]!=p && son[fa[p]][1]!=p;}
inline void sets(int f,int s,int d){son[f][d]=s;fa[s]=f;}
inline void updata(int p){sz[p]=sz[son[p][0]]+sz[son[p][1]]+1;}
void rotate(int p)
{
	int Fa=fa[p];
	int d=getd(p);
	isrt(Fa)?(void)(fa[p]=fa[Fa]): sets(fa[Fa],p,getd(Fa));
	sets(Fa,son[p][d^1],d);
	sets(p,Fa,d^1);
	updata(Fa);
}
void splay(int p)
{
	while(isrt(p)==0)
	{
		if(isrt(fa[p])==0)
			getd(fa[p]) == getd(p)? rotate(fa[p]): rotate(p);
		rotate(p);
	}
	updata(p);
}
void access(int p)
{
	int y=0;
	while(p!=0)
	{
		splay(p);
		son[p][1]=y;
		y=p;
		p=fa[p];
	}
}
int main()
{
	n=RD();
	for(int i=1,p;i<=n;i++) fa[i]= (p=i+ RD())<=n? p: n+1;
	for(int i=RD(),v1,v2,p;i;i--)
	{
		if(RD()==1)
		{
			v1=RD()+1;
			access(v1);
			splay(v1);
			printf("%d\n",sz[son[v1][0]]);
		}
		else
		{
            v1=RD()+1;
            v2= (p=RD()+v1)<=n? p: n+1;
            access(v1);
            splay(v1);
            fa[son[v1][0]]=0;
            son[v1][0]=0;
            fa[v1]=v2;
            access(v1);
            splay(v1);
		}
	}
	return 0;
}
