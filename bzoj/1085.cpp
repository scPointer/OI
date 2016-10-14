#include <cstdio>
inline int gc()
{
	char cr;
	while( (cr=getchar())!='0' && cr!='1' && cr!='*');
	if(cr=='*') return -1;
	else return cr-'0';
}
int goal[5][5]={
{1,1,1,1,1},
{0,1,1,1,1},
{0,0,-1,1,1},
{0,0,0,0,1},
{0,0,0,0,0}};
int mp[5][5];
int px[8]={1,2,2,1,-1,-2,-2,-1},py[8]={2,1,-1,-2,-2,-1,1,2};
inline void swap(int& a,int& b)
{
	int temp=a;a=b;b=temp;
}
inline int check()
{
	int diff=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(mp[i][j]!=goal[i][j])
				diff++;
	return diff;
}
bool dfs(int x0,int y0,int cnt,int lim)
{
	if(cnt==lim)
		return check()==0;
	for(int i=0,nx,ny;i<8;i++)
	{
		nx=x0+px[i];ny=y0+py[i];
		if(nx<0 || nx>=5 || ny<0 || ny>=5) continue;
		swap(mp[x0][y0],mp[nx][ny]);
		if(cnt+check()<=15 && dfs(nx,ny,cnt+1,lim)==1)
			return 1;
		swap(mp[x0][y0],mp[nx][ny]);
	}
	return 0;
}
int solve()
{
	int x0,y0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if((mp[i][j]=gc())==-1)
				x0=i,y0=j;
	for(int i=0;i<=15;i++)
		if(dfs(x0,y0,0,i))
			return i;
	return -1;
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
		printf("%d\n",solve());
}
