#include <cstdio>
#include <algorithm>
#define N 50005
#define eps 1e-10
#define dabs(x) (x>0?(x):-(x))
typedef long double ld;
struct Line{int id;double k,b;}line[N];
struct Point{
    ld x,y;
    Point(ld _x=0,ld _y=0):x(_x),y(_y){}
	friend bool operator<=(Point a,Point b){return a.x<b.x ;}
};
int q[N];
bool cmp(Line a,Line b){return dabs(a.k-b.k)>eps? a.k<b.k: a.b<b.b;}

Point cross(int p1,int p2)
{
    ld x0=((ld)(line[p2].b-line[p1].b))/(line[p1].k-line[p2].k);
    return Point(x0,x0*line[p1].k+line[p1].b);
}
int solve(int n)
{
    std::sort(line+1,line+1+n,cmp);
    int p=1,ltop=0;
    q[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(dabs(line[i].k-line[i-1].k)<eps)
            q[p]=i;
        else q[++p]=i;
    }
    n=p;p=0;
    if(n==1){q[1]=1;return 1;}
    q[++ltop]=q[++p];q[++ltop]=q[++p];
    while(++p<=n)
    {
        while(ltop>1 && cross(q[p],q[ltop])<=cross(q[ltop-1],q[ltop]) )
            ltop--;
        q[++ltop]=q[p];
    }
    return ltop;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&line[i].k,&line[i].b);
        line[i].id=i;
    }
    int ans=solve(n);
    for(int i=1;i<=ans;i++) q[i]=line[q[i]].id;
    std::sort(q+1,q+1+ans);
    for(int i=1;i<=ans;i++)
        printf("%d ",q[i]);
}
