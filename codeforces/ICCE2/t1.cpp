#include <cstdio>
char s1[20],s2[20];
int check(char s[])
{
	if(s[0]=='m') return 0;
	if(s[0]=='t' && s[1]=='u') return 1;
	if(s[0]=='w' && s[1]=='e') return 2;
	if(s[0]=='t' && s[1]=='h') return 3;
	if(s[0]=='f' && s[1]=='r') return 4;
	if(s[0]=='s' && s[1]=='a') return 5;
	return 6;
}
int main()
{
	scanf("%s",s1);
	while(s1[0]<'a' || s1[0]>'z')
		scanf("%s",s1);
	scanf("%s",s2);
	while(s2[0]<'a' || s2[0]>'z')
		scanf("%s",s2);
	int a1=check(s1);
	int a2=check(s2);
	a1=(a2-a1+7)%7;
	if(a1==0 || a1==3 || a1==2)
		puts("YES");
	else puts("NO");
}
