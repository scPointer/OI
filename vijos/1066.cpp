#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 15001
#define MAXI 32001
#define lowbit(i) (i&(-i))
struct point{
	int x,y;
}po[MAXN];
inline bool operator==(point a,point b){return a.x==b.x&&a.y==b.y;}
int c[MAXI],ans[MAXN];
int n,maxy;
bool cmp(point a,point b)
{
	if(a.x!=b.x) return a.x<b.x;
	else return a.y<b.y;
}
void update(int p,int v)
{
	for(;p<=maxy;p+=lowbit(p))
		c[p]+=v;
}
int getsum(int p)
{
	int sum=0;
	for(;p;p-=lowbit(p))
		sum+=c[p];
	return sum;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&po[i].x,&po[i].y);
		if(po[i].y>maxy) maxy=po[i].y;
	}
	sort(po+1,po+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int num=1;
		while(po[i]==po[i+num]) num++;
//		ans[getsum(po[i+num-1].y)+num-1]+=num;
//		update(po[i+num-1].y,num);
		update(po[i+num-1].y,num);
		ans[getsum(po[i+num-1].y)-1]+=num;
		i+=num-1;
	}
	for(int i=0;i<=n-1;i++)
		printf("%d\n",ans[i]);
	return 0;
}
