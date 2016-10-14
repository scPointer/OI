#include <cstdio>
#include <cstring>
#include <iostream>
typedef long long ll;
#define Max(a,b) (a>b?a:b)
int dp[505][505];
int a[505],cnt;
int two[505],tcnt;
int pre[505];
void rd()
{
	char s[505];
	do{
		scanf("%s",s);
	}while(s[0]<'0' || s[0]>'9');
	for(int i=strlen(s)-1;i>=0;i--)
		a[cnt++]=s[i]-'0';
}
void div2()
{
	for(int i=0;i<cnt;i++)
	{
		if(i>0 && (a[i]&1))
			a[i-1]+=5;
		a[i]>>=1;
	}
	while(cnt>0 && a[cnt-1]==0)
		cnt--;
}
void plus(int a[],int b[],int c[])
{
	int lim=Max(b[0],c[0]);
	a[0]=lim;
	a[lim+1]=0;
	for(int i=1;i<=lim;i++)
		if(i<=b[0] && i<=c[0])
			a[i]=b[i]+c[i];
		else if(i<=b[0])
			a[i]=b[i];
		else
			a[i]=c[i];
	for(int i=1;i<=lim;i++)
		if(a[i]>=10)
		{
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
	if(a[lim+1]>0) lim++;
	a[0]=lim;
}
void print(int a[])
{
	for(int i=a[0];i>=1;i--)
		putc(a[i]+'0',stdout);
	puts("");
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		cnt=0;tcnt=0;
		rd();
		while(a[0]%2==0)
		{
			div2();
		}
		while(cnt>0)
		{
			two[tcnt++]=a[0]&1;
			div2();
		}
		pre[tcnt-1]=tcnt-1;
		for(int i=tcnt-2;i>=0;i--)
			pre[i]=two[i]==two[i+1]?pre[i+1]:i+1;
		dp[tcnt-1][0]=1;dp[tcnt-1][1]=1;
		for(int i=tcnt-2;i>=0;i--)
			plus(dp[i],dp[i+1],dp[pre[i+1]]);
		print(dp[0]);
	}
}
