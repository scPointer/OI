#include <cstdio>
#define MAXN 101
int map[MAXN][MAXN];
int n,m;
void init()
{
	scanf("%d%d",&n,&m);
	n++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				map[i][j]=-1;
	for(int i=1;i<=m;i++)
	{
		int st,ed,path;
		scanf("%d%d%d",&st,&ed,&path);
		if(map[st][ed]==-1||map[st][ed]>path) map[st][ed]=path;
	}
}
void floyd()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				for(int k=1;k<=n;k++)
					if(map[i][k]!=-1&&map[k][j]!=-1&&map[i][k]+map[k][j]>map[i][j])
						map[i][j]=map[i][k]+map[k][j];
}
void print()
{
	printf("%d\n%d",map[1][n],1);
	for(int i=2;i<=n;i++)
	{
		if(map[1][i]+map[i][n]==map[1][n])
			printf(" %d",i);
	}
}
int main()
{
	init();
	floyd();
	print();
	return 0;
}
