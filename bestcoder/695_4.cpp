#include <cstdio>
#include <cmath>
#define PI acos(-1)
#define eps 1e-12
int main()
{
	int T; scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		printf("Case #%d:\n",i);
		int n;
		double a,r;
		scanf("%d%lf%lf",&n,&a,&r);
		double minsize=(double)a/2.0*tan((PI-PI*2/n)/2);
		if(r+eps<minsize) printf("Give me a kiss!\n");
		else printf("I want to kiss you!\n");
	}
}