#include <cstdio>
#define N 2000005
#define ND 200005
#define Swap(a,b) {_temp=a;a=b;b=_temp;}
inline int RD(){static int res;scanf("%d",&res);return res;}
char sc[N];
int son[ND][2],fa[ND];
int len[ND],fst[ND],cnt[ND];
bool rev[ND],inrev[ND];
int stk[ND],tops;
int nds;
int _temp;
inline void addNode(int p,int pfst,int plen){cnt[p]=len[p]=plen;fst[p]=pfst;}
inline bool getd(int p){return son[fa[p]][1]==p;}
inline bool isrt(int p){return fa[p]==0;}
inline void sets(int d,int p,int f){son[f][d]=p;fa[p]=f;}
inline void updata(int p){cnt[p]=cnt[son[p][0]]+cnt[son[p][1]]+len[p];}
inline void pushdown(int p);
void rotate(int p);
void splay(int p);
char findkth(int pos,int p);
int find(int pos,int p);
int split(int p,int pos);
inline int mkroot(int ptr);
void insert(int ptr,int pfst,int plen);
void evert(int ptr,int slen);
void remove(int p,int slen);
int main()
{
	int sumlen=0,ptr=0;
	char rds[10],odr;
	for(int Q=RD();Q;Q--)
	{
		scanf("%s",rds);odr=rds[0];
		if(odr=='M')  ptr=RD();
		else if(odr=='P') ptr--;
		else if(odr=='N') ptr++;
		else if(odr=='G')
		{
			char c=findkth(ptr+1,0);
			putchar(c);putchar('\n');
		}
		else if(odr=='I')
		{
			int slen=RD();
			fgets(sc+sumlen,N,stdin);
			while(*(sc+sumlen)=='\n') fgets(sc+sumlen,N,stdin);
			insert(ptr,sumlen,slen);
			sumlen+=slen+3;
		}
		else if(odr=='D')
		{
			int p=mkroot(ptr);
			remove(son[p][1],RD());
			updata(p);
		}
		else
			evert(ptr,RD());
	}
}
inline void pushdown(int p)
{
	if(rev[p])
	{
		Swap(son[p][0],son[p][1])
		rev[p]=0;inrev[p]^=1;
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
	updata(Fa);
//	updata(p);
}
void splay(int p)
{
	tops=0;
	for(int k=p;!isrt(k);k=fa[k]) stk[++tops]=k;
	for(int k=tops;k>=1;k--) pushdown(stk[k]);
	for(int k=1;k<=tops;k++) updata(stk[k]);
	while(!isrt(p))
	{
		if(!isrt(fa[p]))
			getd(p)==getd(fa[p])? rotate(fa[p]): rotate(p);
		rotate(p);
	}
	updata(p);
}
char findkth(int pos,int p)
{
	pushdown(p);
	if(cnt[son[p][0]]>=pos) return findkth(pos,son[p][0]);
	else if(cnt[son[p][0]]+len[p]>=pos)
		return inrev[p]? sc[fst[p]+len[p]-pos]: sc[fst[p]+pos-1];
	else return findkth(pos-cnt[son[p][0]]-len[p],son[p][1]);
}
int find(int pos,int p)
{
	pushdown(p);
	if(p!=0 && son[p][1]==0 && cnt[son[p][0]]+len[p]<pos) return -p;
	if(cnt[son[p][0]]>=pos) return find(pos,son[p][0]);
	else if(cnt[son[p][0]]+len[p]>=pos) return p;
	else return find(pos-cnt[son[p][0]]-len[p],son[p][1]);
}
int split(int p,int pos)
{
	addNode(++nds,fst[p]+pos,len[p]-pos);
	len[p]=pos;
	inrev[nds]=inrev[p];
	if(inrev[p])
	{sets(getd(p),nds,fa[p]);sets(0,son[p][0],nds);sets(1,p,nds);
	updata(p);updata(nds);return nds;}
	else{sets(1,son[p][1],nds);sets(1,nds,p);
	updata(nds);updata(p);return p;}
	
}
inline int mkroot(int ptr)
{
	int p=find(ptr,0);
	splay(p);
	if(len[p]+cnt[son[p][0]]>ptr)
		return inrev[p]? split(p,len[p]-(ptr-cnt[son[p][0]])): split(p,ptr-cnt[son[p][0]]);
	else return p;
}
void insert(int ptr,int pfst,int plen)
{
	addNode(++nds,pfst,plen);
	int newnd=nds;
	if(nds==1){sets(0,newnd,0);return;}
	mkroot(ptr);
	int p=find(ptr+1,0);
	p<0? sets(1,newnd,p): sets(0,newnd,p);
	splay(newnd);
}
void evert(int ptr,int slen)
{
	int res=find(ptr+slen+1,0);
	if(res<0 && ptr==0)
	{
		rev[son[0][0]]^=1;
		return;
	}
	else if(res<0)
	{
		int p=mkroot(ptr);
		rev[son[p][1]]^=1;
		return;
	}
	else if(ptr==0)
	{
		int p=mkroot(ptr+slen);
		p=mkroot(ptr+slen+1);
		rev[son[p][0]]^=1;
		return;
	}
	int p=mkroot(ptr);
	mkroot(ptr+slen);
	mkroot(ptr);
	mkroot(ptr+slen+1);
	if(son[p][1]!=0) rev[son[p][1]]^=1;
}
void remove(int p,int slen)
{
	if(p==0) return;
	pushdown(p);
	if(slen>=cnt[p]) son[fa[p]][getd(p)]=0;
	else if(cnt[son[p][0]]>=slen) remove(son[p][0],slen);
	else if(cnt[son[p][0]]+len[p]>=slen)
	{
		son[p][0]=0;
		int p2=inrev[p]? split(p,len[p]-slen): split(p,slen);
		sets(1,son[p2][1],fa[p2]);
//		updata(p2);
	}
	else
	{
		sets(getd(p),son[p][1],fa[p]);
		remove(son[p][1],slen-cnt[son[p][0]]-len[p]);
	}
	updata(p);
}