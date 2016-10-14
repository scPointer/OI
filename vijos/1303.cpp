#include <cstdio>
#include <cstring>
#define MAXN 25
int height[MAXN];
int h[MAXN];
char s[250];
int readin()
{
	int count=0,num=0;
	scanf("%s",s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
		if(s[i]>='0'&&s[i]<='9')
			num=num*10+s[i]-'0';
		else
		{
			height[++count]=num;
			num=0;
		}
	height[++count]=num;
	return count;
}
int main()
{
	int n=readin();
	int ans=1;
	h[1]=height[1];
	for(int i=2;i<=n;i++)
	{
		int l=0,r=ans+1,mid;
		while(l<r-1)
		{
			mid=(l+r)/2;
			if(height[i]<=h[mid]) l=mid;
			else r=mid;
		}
		h[l+1]=height[i];
		if(l+1>ans) ans=l+1;
	}
	printf("%d,",ans);
	
	memset(h,0,sizeof(h));
	ans=1;
	h[1]=height[1];
	for(int i=2;i<=n;i++)
	{
		int l=0,r=ans+1,mid;
		while(l<r-1)
		{
			mid=(l+r)/2;
			if(height[i]>=h[mid]) l=mid;
			else r=mid;
		}
		h[l+1]=height[i];
		if(l+1>ans) ans=l+1;
	}
	printf("%d",ans-1);
	return 0;
}
