#include <cstdio>
#include <iostream>
#define N 2000005
#define INF 10000000000000000ll
typedef long long ll;
int a[N];
int pre[N];
int cnt;
void init()
{
	char cr;
	while( (cr=getchar())<'a' || cr>'z');
	a[++cnt]=cr-'a'+1;
	while( (cr=getchar())>='a' && cr<='z')
		a[++cnt]=cr-'a'+1;
}
void kmp()
{
	pre[1]=0;
	for(int i=2;i<=cnt;i++)
	{
		int j=pre[i-1];
		while(j && a[j+1]!=a[i]) j=pre[j];
		pre[i]= a[j+1]==a[i]? j+1 :0;	
	}
}

int eg[N<<1],nxt[N<<1],head[N],egtot;
int q[N];
ll len[N<<1],dis[N];
void addEdge(int p1,int p2,ll length)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	len[egtot]=length;
	head[p1]=egtot;
}
ll findfurthest(int S,int& res,int nds=cnt+1)
{
	for(int i=1;i<=nds;i++)
		dis[i]=INF;
	dis[S]=0;res=S;
	int l,r,p;q[l=r=1]=S;
	while(l<=r)
	{
		p=q[l++];
		for(int e=head[p];e;e=nxt[e])
			if(dis[eg[e]]>dis[p]+len[e])
			{
				dis[eg[e]]=dis[p]+len[e];
				q[++r]=eg[e];
				if(dis[eg[e]]>dis[res])
					res=eg[e];
			}
	}
	return dis[res];
}
int main()
{
	freopen("savemzx.in","r",stdin);
	freopen("savemzx.out","w",stdout);
	init();
	kmp();
	for(int i=1;i<=cnt;i++)
	{
		addEdge(i+1,pre[i]+1,(ll)(i-pre[i])*(i-pre[i]));
		addEdge(pre[i]+1,i+1,(ll)(i-pre[i])*(i-pre[i]));
	}
	int p1,p2;findfurthest(1,p1);
	std::cout<<findfurthest(p1,p2);
}
