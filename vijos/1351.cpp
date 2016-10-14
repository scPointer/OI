#include <cstdio>
#define MAXN 2050
#define MIN(a,b) (a<b?a:b)
int map[2][MAXN];
int left[2][MAXN];
int right[2][MAXN];
int up[2][MAXN];
struct Stack{
	inline void reset(int p0=0,int v0=0){p=p0;v=v0;};
	int p,v;
}stk[MAXN];//the place and the value of array-up
int stktop;

int n,m;
int ansrect,anssqu,area;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		map[0][i]=100;
	int x=0;
	for(int i=1;i<=n;i++)
	{
		x=1-x;
		int lmt;
		for(int j=1;j<=m;j++)
			scanf("%d",&map[x][j]);
		for(int j=1;j<=m;j++)
			up[x][j]=map[x][j]!=map[1-x][j]?up[1-x][j]+1:1;
		lmt=1;//limit: if two neighbouring cells has same color,
		//they CANNOT be connected even if Array "up" allows that 
		left[x][1]=0;
		stk[stktop=1].reset(1,up[x][1]);
//		stk[0].reset();
		for(int j=2;j<=m;j++)
		{
			if(map[x][j]==map[x][j-1]) lmt=j;
			
			while(stktop>0&&stk[stktop].v>=up[x][j]) stktop--;
			left[x][j]=lmt<stk[stktop].p?j-stk[stktop].p-1:j-lmt;
			//An example: 1 1 0
			//***********0 0 1
			//lmt=2 stk[stktop].p=1
			if(left[x][j]<0) left[x][j]=0;
			stk[++stktop].reset(j,up[x][j]);
		}
		lmt=m;
		right[x][m]=0;
		stk[stktop=1].reset(m,up[x][m]);
//		stk[0].reset();
		for(int j=m-1;j>=1;j--)
		{
			if(map[x][j]==map[x][j+1]) lmt=j;
			
			while(stktop>0&&stk[stktop].v>=up[x][j]) stktop--;
			right[x][j]=lmt>stk[stktop].p?stk[stktop].p-j-1:lmt-j;
			if(right[x][j]<0) right[x][j]=0;
			stk[++stktop].reset(j,up[x][j]);
		}
		for(int j=1;j<=m;j++)
		{	
			area=up[x][j]*(left[x][j]+right[x][j]+1);
			if(area>ansrect) ansrect=area;
			area=MIN(up[x][j],left[x][j]+right[x][j]+1);
			area=area*area;
			if(area>anssqu) anssqu=area;
		}
	}
	printf("%d\n%d",anssqu,ansrect);
	return 0;
}
