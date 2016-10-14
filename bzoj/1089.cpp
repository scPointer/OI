#include <cstdio>
#define N 69
struct Bigint{
	int a[N],top;
	Bigint(int p=0):top(0){for(int i=N-1;i>0;i--) a[i]=0;a[0]=p;}
	void operator =(const Bigint& ot)
	{
		for(int i=top=ot.top;i>=0;i--)
			a[i]=ot.a[i];
		for(int i=top+1;i<N;i++) a[i]=0;
	}
	void operator *=(const Bigint& ot)
	{
		Bigint c;
		for(int i=0;i<=top;i++)
			for(int j=0;j<=ot.top;j++)
				c.a[i+j]+=a[i]*ot.a[j];
		int i,pre;
		for(i=0,pre=0;i<=top+ot.top || pre!=0;i++)
			if((a[i]=c.a[i]+pre)>=1000)
			{
				pre=a[i]/1000;
				a[i]%=1000;
			}
			else pre=0;
		top=i-1;
	}
	void operator +=(const Bigint& ot)
	{
		int i,pre;
		for(i=0;i<=ot.top;i++)
			a[i]+=ot.a[i];
		for(i=0,pre=0;i<=ot.top || pre!=0;i++)
			if((a[i]+=pre)>=1000)
			{
				pre=a[i]/1000;
				a[i]%=1000;
			}
			else pre=0;
		if(ot.top>top) top=ot.top;
		if(i-1>top) top=i-1;
	}
	void operator -=(const Bigint& ot)
	{
		int i,pre;
		for(i=0;i<=ot.top;i++)
			a[i]-=ot.a[i];
		for(i=0,pre=0;i<=ot.top || pre!=0;i++)
			if((a[i]+=pre)<0)
			{
				pre=-1;
				a[i]+=1000;
			}
			else pre=0;
		if(ot.top>top) top=ot.top;
		if(i-1>top) top=i-1;
		while(top>0 && a[top]==0) top--;
	}
	void print()
	{
		printf("%d",a[top]);
		for(int i=top-1;i>=0;i--)
			printf("%03d",a[i]);
		printf("\n");
	}
}ans,sumans;
int main()
{
	int n,d;
	scanf("%d%d",&n,&d);
	ans=(Bigint)(1);sumans=ans;
	for(int i=1;i<=d;i++)
	{
		ans=(Bigint)(1);
		for(int j=1;j<=n;j++)
			ans*=sumans;
		ans-=sumans;
		ans+=(Bigint)(1);
		sumans+=ans;
	}
	ans.print();
}
