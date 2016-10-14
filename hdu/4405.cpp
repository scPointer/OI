#include <cstdio>
#define N 100011
double f[N];
int next[N];
int main()
{
	int n,m;
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(n==0 && m==0) break;
		for(int i=0;i<=n+6;i++) f[i]=0,next[i]=0;
		for(int i=1,p1,p2;i<=m;i++){
			scanf("%d%d",&p1,&p2);
			next[p1]=p2;
		}
		for(int i=n-1;i>=0;i--)
			if(next[i]) f[i]=f[next[i]];else{
				for(int j=1;j<=6;j++)
					f[i]+=f[i+j];
				f[i]=f[i]/6+1;
			}
		printf("%.4lf\n",f[0]);
	}
	return 0;
}