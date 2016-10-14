#include <cstdio>
#include <algorithm>
#define N 53
inline int RD()
{
	int res;char cr;
	while( (cr=getchar())<'0' || cr>'9'); res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9') res=res*10+cr-'0';
	return res;
}
struct Temp{int p,w;}tp[N][N];
inline bool cmp(Temp a,Temp b){return a.w<b.w;}
int cnt[N];
int pl[N][N],pr[N][N];
double wl[N][N],wr[N][N];
double pi[N],w1[N],w2[N];
double f[N][N],g[N][N];
void init(int line,int wei,int n)
{
	for(int i=1;i<=n;i++)
		if(i==line) pi[i]=w1[i]=w2[i]=0;
		else
		{
			int x=1;
			while(x<=cnt[i] &&(tp[i][x].w<wei ||(tp[i][x].w==wei && i<line))) x++;
			--x;
			if(tp[i][x].w>wei ||(tp[i][x].w==wei && i>line)) --x;
			pi[i]=pl[i][x]/10000.0;
			w1[i]=wl[i][x];
			w2[i]=wr[i][x+1];
		}
}
int main()
{
	freopen("p0000.in","r",stdin);
	int n,m; n=RD();m=RD() -1;
	for(int i=1;i<=n;i++)
	{
		cnt[i]=RD();
		for(int j=1;j<=cnt[i];j++)
		{
			tp[i][j].w=RD();
			tp[i][j].p=RD();
		}
		std::sort(tp[i]+1,tp[i]+cnt[i]+1,cmp);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=cnt[i];j++)
		{
			pl[i][j]=pl[i][j-1]+tp[i][j].p;
			wl[i][j]=wl[i][j-1]+tp[i][j].p/10000.0*tp[i][j].w;
		}
		for(int j=1;j<=cnt[i];j++)
			wl[i][j]/=pl[i][j]/10000.0;
		for(int j=cnt[i];j>=1;j--)
			wr[i][j]=wr[i][j+1]+tp[i][j].p/10000.0*tp[i][j].w;
		for(int j=cnt[i];j>=1;j--)
			wr[i][j]/=(10000-pl[i][j-1])/10000.0;
	}
	double ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=cnt[i];j++)
		{
			init(i,tp[i][j].w,n);
			memset(f,0,sizeof(f));
			memset(g,0,sizeof(g));
			f[0][0]=1;
			for(int k=1;k<=n;k++)
				if(k==i){
					for(int l=0;l<=m;l++)
						f[k][l]=f[k-1][l];
				}
				else{
					for(int l=0;l<=m;l++)
						if(l==0) f[k][l]=f[k-1][l]*pi[k];
						else f[k][l]=f[k-1][l]*pi[k]+f[k-1][l-1]*(1-pi[k]);
				}
			double res=0;
			for(int k=0;k<=m;k++) res+=f[n][k];
//			printf("%.9lf\n",res);
			ans+=res*tp[i][j].w*tp[i][j].p/10000.0;
			//g[0][0]=0;
/*			for(int k=1;k<=n;k++)
				if(k==i){
					for(int l=0;l<=m;l++)
						g[k][l]=g[k-1][l];
				}
				else{
					for(int l=0;l<=m;l++)
						if(l==0) g[k][l]=g[k-1][l]*f[k-1][l];
//						else g[k][l]=g[k-1][l]*f[k-1][l]+(g[k-1][l-1]+w2[k])*f[k-1][l-1];
						else g[k][l]=g[k-1][l]*+(g[k-1][l-1]+w2[k])*(1-pi[k]);
				}
				*//*
			g[n][m]=0;
			for(int k=n-1;k>=0;k--)
				if(k==i){
					for(int l=0;l<=m;l++)
						g[k][l]=g[k+1][l];
				}
				else
				{
					for(int l=0;l<=m;l++)
						g[k][l]=pi[k+1]*g[k+1][l]+(1-pi[k+1])*(g[k+1][l+1]+w2[k]);
				}
			g[n][m]=g[0][0];
			printf("ky= %.9lf * %lf = %.9lf\n",f[n][m]*(g[n][m]+tp[i][j].w),tp[i][j].p/10000.0,f[n][m]*(g[n][m]+tp[i][j].w)*tp[i][j].p/10000.0);
			printf("f=%.9lf g=%.9lf\n",f[n][m],g[n][m]);
			ans+=f[n][m]*(g[n][m]+tp[i][j].w)*tp[i][j].p/10000.0;
			*/
		}
	printf("%.9lf",ans);
}
/*
2 2
4
7 5000
4 3000
3 1000
2 1000
2
5 5000
6 5000

2 1
2
3 5000
4 5000
2
5 5000
6 5000

2 2
2
100 3000
300 7000
2
200 6000
400 4000

3 2
2
1 100
100 9900
2
1 9900
100 100
1
50 10000

3 2
2
0 5000
1000 5000
2
0 5000
1000 5000
1
500 10000
*/