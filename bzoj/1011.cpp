#include <cstdio>
#define N 100005
#define eps 1e-10
#define dabs(x) (x>0?(x):-(x))
int n;
double ap;
int w[N];
long long sumw[N];
double ans1[N],ans2[N];
int main()
{
	freopen("1011.in","r",stdin);
	scanf("%d%lf",&n,&ap);sumw[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&w[i]);
		sumw[i]=sumw[i-1]+w[i];
	}
//	if(n<=5000)
	{
		for(int i=1;i<=n;i++)
		{
			if(i%1000==0) printf("run1 %d\n",i);
			double ans=0;
			for(int j=(int)(i*ap+eps);j>=1;j--)
				ans+=(double)(w[j])/(i-j);
//			printf("%lf\n",ans*w[i]);
			ans1[i]=ans*w[i];
		}
	}

//	else
	{
		for(int i=1;i<=5000;i++)
		{
//			if(i%1000==0) printf("run2 %d\n",i);
			double ans=0;
			for(int j=(int)(i*ap+eps);j>=1;j--)
				ans+=(double)(w[j])/(i-j);
//			printf("%lf\n",ans);
			ans2[i]=ans*w[i];
		}
		
		for(int i=5001,j;i<=n;i++)
		{
//			if(i%1000==0) printf("run2 %d\n",i);
			double ans=0;
			int lim=(int)(i*ap+eps);
			for(j=0;j+lim/50<=lim;j+=lim/50)
				ans+=(double)(sumw[j+lim/50]-sumw[j])/(i-(j+lim/100));
			ans+=(double)(sumw[lim]-sumw[j])/(i-(j+lim)/2);
//			printf("%lf\n",ans*w[i]);
			ans2[i]=ans*w[i];
		}
	}
	
	for(int i=5001;i<=n;i++)
		if(dabs(ans1[i]-ans2[i])/ans1[i]>0.05)printf("%d]%lf %lf\n",i,ans1[i],ans2[i]);
}
