#include <cstdio>
#include <algorithm>
#define Min(a,b) (a<b?a:b)
int a[1005];
int check(int sum,int bt,int& res)
{
	int cnt=bt-1;sum-=cnt;
	for(int i=1;i<=cnt;i++) a[i]=1;
	int now=bt;
	while(sum>=now)
	{
		sum-=now;
		a[++cnt]=now;
		now<<=1;
	}
	if(sum==0) return res=cnt,1;
	else if(sum==1) return a[cnt+1]=sum,res=cnt+1,1;
	else
	{
		int setsum=sum;
		while(sum>bt && (sum&1)==0)
			sum>>=1;
		if(sum==bt) return a[cnt+1]=1,a[cnt+2]=setsum-1,res=cnt+2,0;
		else return a[cnt+1]=setsum,res=cnt+1,1;
	}
}
int main()
{
	int n;scanf("%d",&n);
	if(n==1){printf("1\n1");return 0;}
	int ans=(int)1e9;
	int res;
	for(int i=2;i<=n;i++)
	{
		int sec=check(n,i,res);
		ans=Min(ans,res);
		if(sec) break;
	}
	std::sort(a+1,a+1+ans);
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%d ",a[i]);
}
