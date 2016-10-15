#include <cstdio>
#include <cstring>
char s[105][105];
char psw[105];
int len[105];
int main()
{
	int anslen=0;
	int cnt=0;
	int n,k;scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		do{
			scanf("%s",s[i]);
		}while(s[i][0]=='\n' || s[i][0]==' ');
		len[strlen(s[i])]++;
	}
	do{
			scanf("%s",psw);
	}while(psw[0]=='\n' || psw[0]==' ');
	for(int i=1;i<=n;i++)
		if(strcmp(psw,s[i])==0)
		{
			anslen=strlen(s[i]);
			cnt++;
		}
	int mn=0;
	for(int i=1;i<anslen;i++)
		mn+=len[i];
	printf("%d ",mn+mn/k*5+1);
	mn=mn+len[anslen]-cnt;
	printf("%d\n",mn+mn/k*5+1);
}
