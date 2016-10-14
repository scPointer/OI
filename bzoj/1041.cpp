#include <cstdio>
#include <cmath>
int main()
{
	int n;
	scanf("%d",&n);
	int sqr=(int)(sqrt(n)+0.5);
	int ans=1;
	for(int i=2,cnt;i<=sqr;i++)
		if(n==1) break;
		else if(n%i==0)
		{
			for(cnt=0;n%i==0;n/=i) cnt+=2;
			if(i%4==1) ans*=(cnt+1);
		}
	if(n>1 && n%4==1) ans*=3;
	printf("%d\n",ans*4);
}