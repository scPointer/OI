#include <cstdio>
#define N 1005
#define mo 10000
int f[2][N];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	f[0][0]=1;
	for(int i=1;i<=n-1;i++)
	{
		f[1][0]=f[0][0];
		for(int j=1;j<=k;j++)
			f[1][j]=(f[1][j-1]+f[0][j])%mo;

		for(int j=0;j<=k;j++)
			if(j<=i)
				f[0][j]=f[1][j];
			else
				f[0][j]=(f[1][j]-f[1][j-i-1]+mo)%mo;
	}
	printf("%d",f[0][k]);
}
