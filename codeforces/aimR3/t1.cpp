#include <cstdio>
#include <cstring>
#define N 100005
char s[N];
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	bool used=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]>'a')
		{
			used=1;
			s[i]--;
		}
		else if(used==1 && s[i]=='a')
			break;
	}
	if(used==0) s[len-1]='z';
	printf("%s",s);
}
