#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 53
#define eps 1e-22
inline int RD()
{
	int res;char cr;
	while( (cr=getchar())<'0' || cr>'9'); res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9') res=res*10+cr-'0';
	return res;
}
struct Temp{int p,w;}tp[N][N];
struct Node{int prep,ps,p,w,belx,bely;}nd[N*N];
inline bool cmpT(Temp a,Temp b){return a.w<b.w;}
inline bool cmpN(Node a,Node b){return a.w<b.w;}
int cnt[N];
int pl[N][N];
int calc,rebcnt;
struct Poly{
	long double a[N];
	int ts;
	Poly(int x0=0){ts=0;a[0]=x0;for(int i=1;i<N;i++) a[i]=0;}
//	long double& operator[](int p){return a[p];}
	void mult(long double x0,long double x1,Poly& temp)
	{
		for(int i=0;i<=ts;i++) temp.a[i+1]=a[i]*x1,a[i]*=x0;
		for(int i=1;i<=ts+1;i++) a[i]+=temp.a[i];
		ts++;
	}
	void div(long double x0,long double x1,Poly& temp)
	{
		if(x0<eps)
		{
			for(int i=0;i<ts;i++) a[i]=a[i+1];
			a[ts]=0;
			--ts;
			return;
		}
		if(x1<eps)
		{
			for(int i=0;i<ts;i++) a[i]/=x0;
			a[ts]=0;
			--ts;
			return;
		}
		for(int i=ts;i>=1;i--)
		{
			if(a[i]<eps) {temp.a[i-1]=0;continue;}
			temp.a[i-1]=a[i]/x1;
			a[i]=0;
			a[i-1]-=temp.a[i-1]*x0;
		}
		
/*		for(int i=0;i<ts;i++)
		{
			if(a[i]<eps){temp.a[i]=0;continue;}
			temp.a[i]=a[i]/x0;
			a[i]=0;
			a[i+1]-=temp.a[i+1]*x1;
		}
		*/
		for(int i=0;i<ts;i++)
			a[i]=temp.a[i];
		--ts;
	}
	bool check()
	{
		long double res=1;
		for(int i=0;i<=ts;i++) res-=a[i];
//		printf("deeeeeeeee  %.18lf\n",res);
		if(res<-eps || res>eps) return 1;
		else return 0;
	}
	void print()
	{
		printf("calc %d:",++calc);
		for(int i=0;i<=ts;i++) printf("%.18lf ",(double)a[i]);
		puts("");
	}
	long double getlower(int p)
	{
//		print();
		long double res=0;
		for(int i=0;i<p && i<=ts;i++)
			res+=a[i];
		return res;
	}
	
};
Poly poly,temp;
long double pi[N],f[N][N];
void init(int line,int wei,int n)
{
	for(int i=1;i<=n;i++)
		if(i==line) pi[i]=0;
		else
		{
			int x=1;
			while(x<=cnt[i] &&(tp[i][x].w<wei ||(tp[i][x].w==wei && i<line))) x++;
			--x;
			if(tp[i][x].w>wei ||(tp[i][x].w==wei && i>line)) --x;
			pi[i]=pl[i][x]/10000.0;
		}
}
void force_calc(int n,int i,int j)
{
	++rebcnt;
	init(i,tp[i][j].w,n);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int k=1;k<=n;k++)
		if(k==i){
			for(int l=0;l<=n;l++)
				f[k][l]=f[k-1][l];
		}
		else{
			for(int l=0;l<=n;l++)
				if(l==0) f[k][l]=f[k-1][l]*pi[k];
				else f[k][l]=f[k-1][l]*pi[k]+f[k-1][l-1]*(1-pi[k]);
		}
	for(int k=0;k<=n-1;k++) poly.a[k]=f[n][k];
//	printf("%.9lf\n",res);
//	ans+=res*tp[i][j].w*tp[i][j].p/10000.0;
}
int main()
{
	freopen("p0000.in","r",stdin);
//	freopen("p0000.out","w",stdout);
	int n,m; n=RD();m=RD();
	for(int i=1;i<=n;i++)
	{
		cnt[i]=RD(); cnt[0]+=cnt[i];
		for(int j=1;j<=cnt[i];j++)
		{
			tp[i][j].w=RD();
			tp[i][j].p=RD();
		}
		std::sort(tp[i]+1,tp[i]+cnt[i]+1,cmpT);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=cnt[i];j++)
			pl[i][j]=pl[i][j-1]+tp[i][j].p;
	int top=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=cnt[i];j++)
			nd[++top]=(Node){pl[i][j-1],pl[i][j],tp[i][j].p,tp[i][j].w,i,j};
	std::sort(nd+1,nd+1+top,cmpN);
	
	long double ans=0;
	poly.a[n-1]=1;poly.ts=n-1;
	ans+=poly.getlower(m)*(nd[1].p/10000.0)*nd[1].w;
	for(int i=2;i<=top;i++)
	{
		
		poly.div(nd[i].prep/10000.0,1-nd[i].prep/10000.0,temp);
		poly.mult(nd[i-1].ps/10000.0,1-nd[i-1].ps/10000.0,temp);
		if(poly.check()) force_calc(n,nd[i].belx,nd[i].bely);
		ans+=poly.getlower(m)*(nd[i].p/10000.0)*nd[i].w;
//		printf("ans+=%lf\n",poly.getlower(m));
//			for(int k=1;k<=n;k++)
//					for(int l=0;l<=m;l++)
//						if(l==0) f[k][l]=f[k-1][l]*pi[k];
//						else f[k][l]=f[k-1][l]*pi[k]+f[k-1][l-1]*(1-pi[k]);
	}
	printf("%.9lf\n",(double)ans);
	printf("top= %d rebuild=%d\n",top,rebcnt);
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
