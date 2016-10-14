#include <cstdio>
#include <iostream>
#include <algorithm>
#define N 100005
#define PRM 1230
inline int RD()
{
	static char cr;
	static int res;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int prm[PRM],pcnt;
bool noprm[10005];
long long hash[PRM];
void pre(int n)
{
	for(int i=2;i<=n;i++)
		if(noprm[i]==0)
		{
			prm[++pcnt]=i;
			for(int j=i*i;j<=n;j+=i)
				noprm[j]=1;
		}
	long long x1=83018977,a=998244353,b=7943712;
	for(int i=1;i<=pcnt;i++) hash[i]=(x1=x1*a+b);
}

int eg[N*2],nxt[N*2],head[N],egtot;
long long wt[N*2];
inline long long gethash(int p)
{
	if(p<=pcnt) return hash[p];
	else return (long long)(p)*998244353;
}
long long calc(int p);
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
	eg[++egtot]=p1;
	nxt[egtot]=head[p2];
	head[p2]=egtot;
	wt[egtot-1]=wt[egtot]=calc(RD());
}
long long w[N];
int fa[N],q[N];
void setTree(int root)
{
	int l,r,p;q[l=r=1]=root;
	while(l<=r)
	{
		p=q[l++];
		for(int i=head[p];i;i=nxt[i])
			if(eg[i]!=fa[p])
				fa[eg[i]]=p,w[eg[i]]=w[p]^wt[i],q[++r]=eg[i];
	}
}
int main()
{
	int n;
	pre(10000);
	for(int i=n=RD();i>1;i--) addEdge(RD(),RD());
	setTree(1);
	std::sort(w+1,w+1+n);w[n+1]=-1;
	long long ans=0;
	for(long long i=1,j=0,fj=0;i<=n;i=j+1,ans+=(j-fj)*(j-fj-1))
		for(fj=j++;w[j]==w[j+1];j++);
	std::cout<<ans;
}
long long calc(int p)
{
	long long rez=0;
	for(int i=1;i<=pcnt && p>1;i++)
		for(;p%prm[i]==0;rez^=gethash(i),p/=prm[i]);
	return p==1? rez: rez^gethash(p);
}
