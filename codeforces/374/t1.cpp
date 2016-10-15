#include <cstdio>
inline char RC()
{
	char cr;
	while( (cr=getchar())<'A' || cr>'Z');
	return cr;
}
int len[105],cnt;
int col[105];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		col[i]= RC()=='B'?1:0;
	for(int i=1;i<=n;i++)
		if(col[i]==1)
		{
			if(col[i-1]==1) len[cnt]++;
			else len[++cnt]=1;
		}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",len[i]);
}
