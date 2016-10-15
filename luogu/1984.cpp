#include <cstdio>
int main()
{
	int n;scanf("%d",&n);
	double ans=1,mul=1;
	for(int i=1;i<n;i++)
		ans+=(mul*=(i*2-1)/(double)(i*2));
	printf("%.2lf",ans*420000/n);
}