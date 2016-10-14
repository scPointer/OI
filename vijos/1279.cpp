#include <cstdio>
#define swap(x,y,s) {s=x;x=y;y=s;}
long long a,b,ans;
int main()
{	
	for(int i=1;i<=10;i++)
	{
		a=b=ans=0;
		scanf("%lld%lld",&a,&b);
		long long sw;
		if(a<b) swap(a,b,sw);
		if(a==b) ans=a;
		else
			while(b!=0)
			{
				ans+=a-a%b;
				a-=a-a%b;
				if(a<b) swap(a,b,sw);
			}
		printf("%I64d\n",ans);
	}
	return 0;
}
