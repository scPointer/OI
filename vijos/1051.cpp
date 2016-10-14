#include <cstdio>
//#include <cstring>
#define MAXN 101
const int near[12][2]={{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,-1},{-1,1},{1,1},{0,2},{2,0},{0,-2},{-2,0}};
int map[MAXN][MAXN];
int queue[MAXN*MAXN][2];
int n,m;
void work(int x0,int y0)
{
//	memset(queue,0,sizeof(queue));
	int st=1,ed=1;
	queue[ed][0]=x0;
	queue[ed][1]=y0;
	while(ed<=st)
	{
		int x,y;
		for(int i=0;i<=11;i++)
		{
			x=queue[ed][0]+near[i][0];
			y=queue[ed][1]+near[i][1];
			if(x>=1&&x<=n&&y>=1&&y<=m&&map[x][y]==1)
			{
				st++;
				queue[st][0]=x;
				queue[st][1]=y;
				map[x][y]=-1;
			}
		}
		ed++;
	}
}
int main()
{
	int count=0;
	scanf("%d%d",&n,&m);
	char s[MAXN][MAXN];
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
			if(s[i][j]=='#')
				map[i][j+1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]==1)
			{
				work(i,j);
				count++;
			}
	printf("%d",count);
	return 0;
}
