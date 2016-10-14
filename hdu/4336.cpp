#include <cstdio>
double f[1<<20];
double a[22];
int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=0;i<n;i++)
			scanf("%lf",&a[i]);
		double left=1;
		for(int i=0;i<n;i++) left-=a[i];
		f[(1<<n)-1]=0;
		for(int i=(1<<n)-2;i>=0;i--)
		{
			double up=1,low=0;
			for(int j=0;j<n;j++)
				if((i&(1<<j))==0)
					up+=a[j]*f[i|(1<<j)],low+=a[j];
			f[i]=up/low;
		}
		printf("%.5lf\n",f[0]);
	}
}