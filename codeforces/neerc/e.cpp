#include <cstdio>
#include <algorithm>
#define swap(a,b) std::swap(a,b)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
int bef[105];//before
int dlt[105];//delta
inline bool less(int xv,int x,int yv,int y)
{
	return xv==yv? x>y:xv<yv;
}
int check(int x,int y)
{
	int lx=Min(bef[x],bef[x]+dlt[x]);
	int rx=Max(bef[x],bef[x]+dlt[x]);
	int ly=Min(bef[y],bef[y]+dlt[y]);
	int ry=Max(bef[y],bef[y]+dlt[y]);
	if(less(ly,y,lx,x))
		swap(x,y),swap(lx,ly),swap(rx,ry);
	if(less(rx,x,ly,y))
		return 0;
	bool dirx= (dlt[x]>0);
	bool diry= (dlt[y]>0);
	if(dirx!=diry)
		return 1;
	else if(less(ry,y,rx,x))
		return 1;
	else return 2;
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&bef[i],&dlt[i]);
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans+=check(i,j);
	printf("%d",ans);
}