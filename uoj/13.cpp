#include <cstdio>
#include <cstring>
#define N 500050
char s[N],*cp=s,cr[N],ans[N];
int leap[N],son[N][28],dad[N],tot;
int n,m,len;
int setpath()
{
	int p=1,dt;
	while(*cp!='/') cp++;
	while((*cp>='a' && *cp<='z') || *cp=='/')
	{
		dt= *cp=='/'? 27:*cp-'a'+1;
		if(!son[p][dt]){son[p][dt]=++tot;dad[tot]=p;}
		p=son[p][dt];
		cr[p]=*cp;
		while(leap[p] && (*(cp+1)==' '||*(cp+1)=='/')) p=leap[p];
		cp++;
	}
	return p;
}
void findpath()
{
	int p=1,dt,cnt=0;
	while(*cp!='/') cp++;
	while((*cp>='a' && *cp<='z') || *cp=='/')
	{
		dt= *cp=='/'? 27:*cp-'a'+1;
		if(!son[p][dt]){son[p][dt]=++tot;dad[tot]=p;}
		p=son[p][dt];
//		printf("[%c]",*cp);
		cr[p]=*cp;
		while(leap[p] && (*(cp+1)=='\n'||*(cp+1)=='/')) p=leap[p];
		cp++;
	}
	while(p!=1)
	{
		ans[++cnt]=cr[p];
		p=dad[p];
	}
	for(int i=cnt;i>=1;i--)
		putchar(ans[i]);
	if(cnt==0) putchar('/');
	putchar('\n');
}
int main()
{
	scanf("%d%d",&n,&m);
	fread(s,sizeof(char),N,stdin);
	len=strlen(s);s[len]='\n';s[len+1]='\0';
	int p1,p2;tot=1;
	while(n--) 
	{
		p1=setpath();
		p2=setpath();
		leap[p1]=p2;
		if(p2==2) leap[p1]=1;
	}
	while(m--)
		findpath();
	return 0;
}
