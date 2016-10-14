#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 1000005
int next[maxn],n;
char s[maxn];
void getnext()
{
	next[0]=0;
	for(int i=1;i<n;i++)
	{
		int j=next[i];
		while(j&&s[i]!=s[j]) j=next[j];
		next[i+1]=s[i]==s[j]?j+1:0;
	}
}
int main()
{
	scanf("%s",s);
	n=strlen(s);
	getnext();
	int T=n;
	int ans=n;
	while(next[T]!=0) T--;    //从后删去一定能匹配的
	while(next[ans]>=T)    ans=next[ans];        //找到第一个小于等于T的ans
	printf("%d",ans);
}
