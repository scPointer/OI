#include <cstdio>
#define T 1005
#define M 32
double a[T][M],f[T][M],g[T][M];
double temp[M];
int main()
{
	int m,t,n;
	g[0][1]=1;
	while(~scanf("%d%d%d",&m,&t,&n) && m!=0){
		for(int i=1;i<=t;i++)
			for(int j=1;j<=m;j++){
				scanf("%lf",&a[i][j]);
				f[i][j]=g[i][j]=0;
			}
		for(int i=1;i<=t;i++){
			f[i][0]=1;
			for(int j=1;j<=m;j++){
				for(int k=0;k<j;k++){
					temp[k+1]=f[i][k]*a[i][j];
					f[i][k]*=(1-a[i][j]);
				}
				for(int k=1;k<=j;k++)
					f[i][k]+=temp[k];
			}
		}
		for(int i=1;i<=t;i++)
			for(int j=1;j<=m;j++){
				for(int k=1;k<=j;k++)
					g[i][j]+=g[i-1][k]*f[i][j];
				for(int k=1;k<j;k++)
					g[i][j]+=g[i-1][j]*f[i][k];
			}
		double ans=0;
		for(int i=n;i<=m;i++)
			ans+=g[t][i];
		printf("%.3lf\n",ans);
	}
}