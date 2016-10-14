#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct word{
	char w[260];
	int len;
}wo[1010];
int tll[30],atll[30];//translate list
int n,order;
char dict[30];
int cmp(word a,word b)
{
	int minlen=a.len<b.len?a.len:b.len;
	for(int i=0;i<=minlen-1;i++)
	{
		if(a.w[i]!=b.w[i]) return a.w[i]<b.w[i];
	}
	if(order==1) return a.len<b.len;
	else return a.len>b.len;
}
int main()
{
	scanf("%s",dict);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",wo[i].w);
		wo[i].len=strlen(wo[i].w);
	}
	scanf("%d",&order);
	if(order==1)
		for(int i=0;i<=25;i++)
		{
			int key=dict[i]-'a';
			tll[key]=i;
			atll[i]=key;
		}
	else
		for(int i=0;i<=25;i++)
		{
			int key=dict[i]-'a';
			tll[key]=25-i;
			atll[25-i]=key;
		}
	for(int i=1;i<=n;i++)
		for(int j=wo[i].len-1;j>=0;j--)
			wo[i].w[j]=tll[wo[i].w[j]-'a']+'a';
	sort(wo+1,wo+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=wo[i].len-1;j>=0;j--)
			wo[i].w[j]=atll[wo[i].w[j]-'a']+'a';
		printf("%s\n",wo[i].w);
	}
	return 0;
}
