#include <cstdio>
char RC()
{
	char cr;
	while( (cr=getchar())<'A' || cr>'Z');
	return cr;
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	bool color=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char cr=RC();
			if(cr!='B' && cr!='W' && cr!='G')
				color=1;
		}
	if(color) printf("#Color");
	else printf("#Black&White");
}