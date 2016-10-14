#include <cstdio>
#include <cstring>
#define MAXN 1000050
int f[MAXN];
char na[MAXN];
void kmp(char* s,int len)
{
	f[0]=0;
	for(int i=1;i<len;i++)
	{
		int j=f[i];
		while(j>0&&s[i]!=s[j]) j=f[j];
		f[i+1]= s[j]==s[i]?j+1:0;
	}
}
int main()
{
	scanf("%s",na);
	int len=strlen(na);
	kmp(na,len);
	int minlimit=len,ans=len;
	while(f[minlimit]!=0)
		minlimit--;
	while(f[ans]>=minlimit)
		ans=f[ans];
	printf("%d",ans);
	return 0;
}
