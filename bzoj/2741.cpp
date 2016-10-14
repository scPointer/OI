#include <cstdio>
#include <cmath>
#define N 12005
#define NDS 400005
#define BLK 115
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
typedef long long ll;
char ss[1<<18],*cs,*ct;
inline char gchar()
{
	cs==ct? cs=ss,ct=cs+fread(ss,1,(1<<18)-3,stdin): 0;
	return *cs++;
}
inline int RD()
{
	int res;
	char cr;
	while( (cr=gchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=gchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
int sc[N];
int pre[BLK][N];
int son[NDS][2],cnt[NDS],rot[N],ndcnt;
//const int root=0;
inline void addT(int& rt,int& prt,int c)
{
	son[rt][c^1]=son[prt][c^1];
	rt=son[rt][c]=++ndcnt;
	prt=son[prt][c];
	cnt[rt]=cnt[prt]+1;
}
int update(int prt,int v)
{
	int rt=++ndcnt; cnt[rt]=cnt[prt]+1;
	int setrt=rt;
	for(int i=30;i>=0;i--)
		addT(rt,prt,(v&(1<<i))&&1);//WA1: addT(rt,prt,v&(1<<i));
	return setrt;
}
int query(int lrt,int rrt,int p)
{
	if(lrt>=rrt) return 0;
	int ans=0,c;
	for(int i=30;i>=0;i--)
	{
		c=((p&(1<<i))&&1)^1;//WA2: c=(p&(1<<i))^1;
		if(cnt[son[rrt][c]]-cnt[son[lrt][c]]>0)
			ans|= 1<<i,rrt=son[rrt][c],lrt=son[lrt][c];
		else rrt=son[rrt][c^1],lrt=son[lrt][c^1];
	}
	return ans;
}
int main()
{
	cs=ct=ss;
	int n=RD();n++;
	int Q=RD();
	for(int i=2;i<=n;i++) sc[i]=sc[i-1] ^ RD();
	for(int i=1;i<=n;i++) rot[i]=update(rot[i-1],sc[i]);
	int block=(int)sqrt(n);
	for(int i=1;;i++)
	{
		int st=block*(i-1)+1;
		if(st>n) break;
		for(int j=st;j<=n;j++)
		{
			int res=query(rot[st-1],rot[j-1],sc[j]);
			pre[i][j]=Max(pre[i][j-1],res);
		}
	}
	int lastans=0;
	while(Q--)
	{
		int x=((ll)lastans+RD())%(n-1)+1;
		int y=((ll)lastans+RD())%(n-1)+1;
		int l=Min(x,y),r=Max(x,y)+1;
		int force=(l-1)/block*block+block;//WA4: int force=l/block*block;
		lastans=pre[(l-1)/block+2][r];//WA5: lastans=pre[l/block+1][r];
		for(int i=l;i<=force;i++)
		{
			int res=query(rot[i],rot[r],sc[i]);//WA3:int res=query(rot[i+1],rot[r],sc[i]);
			lastans=Max(lastans,res);
		}
		printf("%d\n",lastans);
	}
}