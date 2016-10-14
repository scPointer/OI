#include <cstdio>
#include <cstring>
char s[15];
int main()
{
	scanf("%s",s);
	if(s[0]=='0') {printf("0");return 0;}
	int p=strlen(s)-1,t=0;
//	if(s[0]=='-') sym=-1;
	if(s[0]=='-')
	{
		printf("-");
		t=1;
	}
	while(p>=0&&s[p]=='0') p--;
	for(int i=p;i>=t;i--)
		printf("%c",s[i]);
	return 0;
}
