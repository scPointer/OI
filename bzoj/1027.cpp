#include <cstdio>
#define N 505
#define eps (1e-12)
#define Abs(x)((x)>0?(x):-(x))
#define INF 1000000007
#define Min(a,b) (a<b?a:b)
struct Point
{
	double x,y;
	Point operator-(const Point& b)
	{
		return (Point){x-b.x,y-b.y};
	}
};
Point pa[N],nd[N];
int dis[N][N];
int m,n;
inline double cross(Point a,Point b)
{
	return a.y*b.x-a.x*b.y;
}
inline bool checkLeft(Point a,Point b,Point p)
{
	return cross(p-a,b-a)>-eps;
}
inline bool checkRight(Point a,Point b,Point p)
{
	return cross(b-a,p-a)>-eps;
}
inline bool issame(Point a,Point b)
{
	return Abs(a.x-b.x)<eps && Abs(a.y-b.y)<eps;
}
bool check_line(Point ls,Point le,Point p)
{
    return !((ls.x>p.x&&le.x>p.x)||(ls.x<p.x&&le.x<p.x)||(ls.y>p.y&&le.y>p.y)||(ls.y<p.y&&le.y<p.y));
}
bool check(Point a,Point b)
{
	for(int i=1;i<=n;i++)
		if(!checkRight(a,b,nd[i])) return 0;
		else if(checkLeft(a,b,nd[i]) && checkRight(a,b,nd[i]) && !check_line(a,b,nd[i])) return 0;
	return 1;
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		double z;
		scanf("%lf%lf%lf",&pa[i].x,&pa[i].y,&z);
	}
	for(int i=1;i<=n;i++)
	{
		double z;
		scanf("%lf%lf%lf",&nd[i].x,&nd[i].y,&z);
	}
	for(int i=1;i<=m;i++)
	{
		bool spj=1;
		for(int j=1;j<=n;j++)
		{
			if(!issame(pa[i],nd[j]))
			{spj=0;break;}
		}
		if(spj){printf("1");return 0;}
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			dis[i][j]=INF;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			if(!issame(pa[i],pa[j]) && check(pa[i],pa[j]))
				dis[i][j]=1;
	for(int k=1;k<=m;k++)
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
				if(dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];
	int ans=INF;
	for(int i=1;i<=m;i++)
		ans=Min(ans,dis[i][i]);
	if(ans<INF) printf("%d",ans);
	else printf("-1");
}