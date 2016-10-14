#include <cstdio>
#define N 105
#define M 20005
#define eps 1e-8
#define Abs(a) ((a)<0?-(a):(a))
#define Swap(a,b) {__t=a;a=b;b=__t;}
int eg[M],nxt[M],wi[M],head[N],egtot;
int deg[N];
void addEdge(int p1,int p2,int w)
{
	deg[p1]++;
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	wi[egtot]=w;
	head[p1]=egtot;
}
double mtx[N][N];
double val[N];
double work(int m)
{
	int p=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=i;j<=m;j++)
			if(Abs(mtx[j][p])>eps)
			{
				double __t;
				for(int k=p;k<=m+1;k++)
					Swap(mtx[i][k],mtx[j][k]);
				break;
			}
		if(Abs(mtx[i][p])<eps) {++p;continue;}
		for(int j=i+1;j<=m;j++)
		{
			double br=mtx[j][p]/mtx[i][p];
			if(Abs(br)<eps) continue;
			for(int k=p;k<=m+1;k++)
				mtx[j][k]-=mtx[i][k]*br;
		}
		p++;
	}
	for(int i=m;i>=1;i--)
	{
		for(int j=i+1;j<=m;j++)
			mtx[i][m+1]+=mtx[i][j]*val[j];
		val[i]=-mtx[i][m+1]/mtx[i][i];
	}
//	printf("%lf\n",val[1]);
	return val[1];
}
double solve(int bit,int n)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			mtx[i][j]=0;
	for(int i=1;i<=n-1;i++)
	{
		mtx[i][i]=-1;
		double each=(double)1/deg[i];
		for(int e=head[i];e;e=nxt[e])
		{
			if(eg[e]==n)
				wi[e]&(1<<bit)? mtx[i][n]+=each:0;
			else if(wi[e]&(1<<bit))
				mtx[i][eg[e]]-=each,mtx[i][n]+=each;
			else mtx[i][eg[e]]+=each;
		}
	}
	return work(n-1);
}
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	for(int i=1,p1,p2,w;i<=m;i++)
	{
		scanf("%d%d%d",&p1,&p2,&w);
		addEdge(p1,p2,w);
		if(p1!=p2) addEdge(p2,p1,w);
	}
	double ans=0;
	for(int i=0;i<30;i++)
		ans+=solve(i,n)*(1<<i);
	printf("%.3lf",ans);
}