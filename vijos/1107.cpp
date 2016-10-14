#include <cstdio>
#include <cstring>
#define MC 1001
struct qp
{
	int x,y;
	int dis;//distance
}queue[MC*MC],furtest;
bool inqueue[MC][MC];
int c,r;
int st,ed;
bool map[MC][MC];
char s[MC];
inline void putin(int x0,int y0,int disi)
{
	st++;
	queue[st].x=x0;
	queue[st].y=y0;
	queue[st].dis=disi+1;
	inqueue[x0][y0]=1;
	if(queue[st].dis>furtest.dis)
		furtest=queue[st];
}
qp findfurthest(int x0,int y0)
{
	memset(inqueue,0,sizeof(inqueue));
	st=1,ed=1;
	queue[ed].x=x0;queue[ed].y=y0;
	queue[ed].dis=0;
	inqueue[x0][y0]=1;
	while(ed<=st)
	{
		int xi=queue[ed].x,yi=queue[ed].y,disi=queue[ed].dis;
		if(xi+1<=r&&map[xi+1][yi]==1&&inqueue[xi+1][yi]==0)
			putin(xi+1,yi,disi);
		if(xi-1>=1&&map[xi-1][yi]==1&&inqueue[xi-1][yi]==0)
			putin(xi-1,yi,disi);
		if(yi+1<=c&&map[xi][yi+1]==1&&inqueue[xi][yi+1]==0)
			putin(xi,yi+1,disi);
		if(yi-1>=1&&map[xi][yi-1]==1&&inqueue[xi][yi-1]==0)
			putin(xi,yi-1,disi);
		ed++;
	}
	return furtest;
}
int main()
{
	scanf("%d%d",&c,&r);
	for(int i=1;i<=r;i++)
	{
		scanf("%s",s);
		int len=strlen(s);
		for(int j=0;j<=len-1;j++)
			if(s[j]=='.') map[i][j+1]=1;
	}
	bool flag=0;
	qp ans;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
			if(map[i][j]==1){ans=findfurthest(i,j);flag=1;break;}
		if(flag==1) break;
	}
	furtest.x=furtest.y=furtest.dis=0;
	ans=findfurthest(ans.x,ans.y);
	printf("%d",ans.dis);
	return 0;
}
