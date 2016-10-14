#include <cstdio>
#include <iostream>
//#include <algorithm>
//using namespace std;
#define MAXN 300005
#define MAXM 300005
#define MAXL 20
inline int RD()
{
	static int res;
	static char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
struct Edge{
	int p1,p2,w,next;
}edge[MAXM*2];
int head[MAXN],edtop;
int n,m,q;
bool vis[MAXN];
int h[MAXN];
int fd[MAXN][MAXL];
long long Fsum[MAXN][MAXL];
void addedge(int p1,int p2,int w)
{
	edtop++;
	edge[edtop].p2=p2;
	edge[edtop].w=w;
	edge[edtop].next=head[p1];
	head[p1]=edtop;
}
void settree(int p)
{
	vis[p]=1;
	int k=head[p];
	while(edge[k].p2!=0)
	{
		if(vis[edge[k].p2]==0)
		{
			int kp=edge[k].p2;
			fd[kp][0]=p;
			Fsum[kp][0]=edge[k].w;
			h[kp]=h[p]+1;
			settree(kp);
		}
		k=edge[k].next;
	}
}
long long func2(int& p,int hei)
{
	int d=MAXL-1;
	long long ret=0;
	while(1)
	{
		while(h[fd[p][d]]<hei) d--;
		ret=ret+Fsum[p][d];
		p=fd[p][d];
		if(h[p]==hei) break;
	}
	return ret;
}
long long function(int p1,int p2)
{
	if(p1==p2) return 0;
	long long smin;
	if(h[p1]!=h[p2]) smin=h[p1]>h[p2]?func2(p1,h[p2]):func2(p2,h[p1]);
	else smin=0;
	if(p1==p2) return smin;
	for(int d=MAXL-1;d>=0;d--)
	{
		if(fd[p1][d]!=fd[p2][d])
		{
			smin+=Fsum[p1][d]+Fsum[p2][d];
			p1=fd[p1][d];p2=fd[p2][d];
		}
	}
	smin+=Fsum[p1][0]+Fsum[p2][0];
	return smin;
}
int main()
{
	n=RD();m=RD();q=RD();
	for(int i=1,p1,p2,w;i<=m;i++)
	{
		p1=RD();p2=RD();w=RD();
		addedge(p1,p2,w);addedge(p2,p1,w);
	}
//	for(int i=1;i<=n;i++)
//		if(vis[i]==0)
//		{
//			fd[i][0]=i;
//			Fsum[i][0]=0;
//			settree(i);
//		}
	fd[1][0]=1;
	settree(1);
	for(int i=1;i<=MAXL-1;i++)
		for(int j=1;j<=n;j++)
		{
			fd[j][i]=fd[fd[j][i-1]][i-1];
			Fsum[j][i]=Fsum[j][i-1]+Fsum[fd[j][i-1]][i-1];
		}
	long long ans;
	for(int i=1,drivers,si,ti,tp;i<=q;i++)
	{
		drivers=RD();ans=0;
		for(int j=1;j<=drivers;j++)
		{
			si=RD();ti=RD();tp=RD();
			ans+=function(si,ti);
		}
		si=RD();
		std::cout<<ans<<std::endl;
	}
	return 0;
}
