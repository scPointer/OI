#include <cstdio>
#define MAXN 1025
int tr[MAXN][MAXN];
int n;
void add(int x0,int y0,int am)
{
	for(;x0<=n;x0+=x0&(-x0))
		for(int i=y0;i<=n;i+=i&(-i))
			tr[x0][i]+=am;
}
int find(int x0,int y0)
{
	int ret=0;
	for(;x0>0;x0-=x0&(-x0))
		for(int i=y0;i>0;i-=i&(-i))
			ret+=tr[x0][i];
	return ret;
}
int main()
{
	scanf("%d",&n);
//	n++;
	int m;
	while(scanf("%d",&m)==1)
	{
		if(m==3) break;
		if(m==1)
		{
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			x++;y++;
			add(x,y,k);
		}
		else if(m==2)
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1++;x2++;y1++;y2++;
			printf("%d\n",find(x2,y2)+find(x1-1,y1-1)-find(x2,y1-1)-find(x1-1,y2));
		}
	}
	return 0;
}
