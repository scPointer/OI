#include <cstdio>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=(res<<3)+(res<<1)+cr-'0';
	return res;
}
#define lowbit(x) (x&(-x))
int cnt[102][302][302];
int col[302][302];
int n,m;
void add(int p,int x,int y,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			cnt[p][i][j]+=v;
}
int sum(int p,int x,int y)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j>0;j-=lowbit(j))
			res+=cnt[p][i][j];
//	printf("res%d\n",res);
	return res;
}
int main()
{
	n=RD();m=RD();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			add(col[i][j]=RD(),i,j,1);
	for(int q=RD();q;q--)
	{
		if(RD()==1)
		{
			int x,y,p;
			x=RD();y=RD();p=RD();
			add(col[x][y],x,y,-1);
			add(col[x][y]=p,x,y,1);
		}
		else
		{
			int x1,y1,x2,y2,p;
			x1=RD();x2=RD();y1=RD();y2=RD();p=RD();
			printf("%d\n",sum(p,x2,y2)+sum(p,x1-1,y1-1)-sum(p,x2,y1-1)-sum(p,x1-1,y2));
		}
	}
}
