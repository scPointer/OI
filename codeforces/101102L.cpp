#include <cstdio>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
#define N 100005
#define INF 1000000
int eg[N<<1],nxt[N<<1],head[N],egtot;
int f[N][5];
inline int Max(int a,int b){return a>b?a:b;}
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
void dfs(int p,int fa)
{
	f[p][0]=f[p][1]=f[p][2]=f[p][3]=f[p][4]=0;
	int sum0=0;
	int mx1=-INF,mx2=-INF,mx3=-INF;
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			int j=eg[i];
			dfs(j,p);
			f[p][0]+=Max(f[j][0],Max(f[j][1],f[j][3]));
			f[p][2]+=f[j][0];
			sum0+=f[j][0];
			int s=f[j][2]-f[j][0];
			if(s>mx1)
				{mx3=mx2;mx2=mx1;mx1=s;}
			else if(s>mx2)
				{mx3=mx2;mx2=s;}
			else if(s>mx3)
				mx3=s;
		}
	if(mx3>-INF) f[p][3]=sum0+mx1+mx2+mx3+1;
	if(mx2>-INF) f[p][4]=sum0+mx1+mx2+1;
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			int j=eg[i];
			f[p][1]=Max(f[p][1],sum0-f[j][0]+f[j][4]);
		}
//	printf("%d %d %d %d %d %d\n",p,f[p][0],f[p][1],f[p][2],f[p][3],f[p][4]);
}
int main()
{
	for(int T=RD();T;T--)
	{
		int n=RD();
		egtot=0;
		for(int i=0;i<=n;i++)
			head[i]=0;
		for(int i=1,p1,p2;i<=n-1;i++)
		{
			p1=RD();p2=RD();
			addEdge(p1,p2);
			addEdge(p2,p1);
		}
		dfs(1,0);
		printf("%d\n",Max(Max(f[1][0],f[1][1]),Max(f[1][2],f[1][3])));
	}
}
/*

2 1 4 1 1
5 1 1 1 1
1 1 1 1 1
在(3,5)这个点的时候
mx[1]=1 pos[1]=1
mx[2]=2 pos[2]=3
mx[3]=3 pos[3]=5

*/