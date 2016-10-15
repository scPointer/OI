#include <cstdio>
#include <cstring>
#define N 300005
char s[N];
int a[N];
int m,len;
bool check(int p)
{
	int cnt=0;
	for(int i=0;i<len;i++)
	{
		a[i]<=p? cnt=0:cnt++;
		if(cnt>=m) return 0;
	}
	return 1;
}
int solve(int p)
{
	int res=0;
	int cnt=0,last=-1;
	for(int i=0;i<len;i++)
	{
		a[i]<p? cnt=0:cnt++;
		if(a[i]==p) last=i;
		if(cnt>=m)
		{
			res++;
			cnt=i-last;
		}
	}
	return res;
}
void calc(int p)
{
	for(int i=0;i<len;i++)
		if(a[i]==p)
			printf("%c",a[i]+'a');
}
int main()
{
	scanf("%d",&m);
	scanf("%s",s);
	while(s[0]<'a' || s[0]>'z') scanf("%s",s);
	len=strlen(s);
	for(int i=0;i<len;i++)
		a[i]=s[i]-'a';
	int p1,p2;
	for(int i=0;i<26;i++)
		if(check(i))
		{
			p1=i;
			p2=solve(i);
			break;
		}
	for(int i=0;i<p1;i++)
		calc(i);
	for(int i=1;i<=p2;i++)
		printf("%c",p1+'a');
}
