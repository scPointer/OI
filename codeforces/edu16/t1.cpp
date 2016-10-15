#include <cstdio>

int main()
{
	char c;
	int n;
	int cnt=0;
	scanf("%c",&c);
	scanf("%d",&n);
	if(c=='a' || c=='h') cnt++;
	if(n==1 || n==8) cnt++;
	if(cnt==0) puts("8");
	else if(cnt==1) puts("5");
	else puts("3");
}