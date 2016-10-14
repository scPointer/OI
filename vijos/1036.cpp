#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 100001
struct city{
	int x,y,w;
}p[MAXN];
int cmpx(city a,city b)
{
	return a.x<b.x;
}
int cmpy(city a,city b)
{
	return a.y<b.y;
}
int main()
{
	int n;
	long long sumx=0,sumy=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int w1,w2;
		scanf("%d%d%d%d",&p[i].x,&p[i].y,&w1,&w2);
		p[i].w=w1*w2;
		sumx+=p[i].w;
		sumy+=p[i].w;
	}
	
	sort(p+1,p+1+n,cmpx);
	long long sum=0;
	int ansx=0;
	for(int i=1;i<=n;i++)
	{
		sum+=p[i].w;
		if(sum*2>sumx)
		{
			if(i==1) ansx=p[i].x;
			else if(sumx/2-(sum-(long long)p[i].x*(long long)p[i].w)<=sum-sumx/2)
				ansx=p[i-1].x;
			else ansx=p[i].x;
			break;
		}
	}
	sort(p+1,p+1+n,cmpy);
	sum=0;
	int ansy=0;
	for(int i=1;i<=n;i++)
	{
		sum+=p[i].w;
		if(sum*2>sumy)
		{
			if(i==1) ansy=p[i].y;
			else if(sumy/2-(sum-(long long)p[i].x*(long long)p[i].w)<=sum-sumy/2)
				ansy=p[i-1].y;
			else ansy=p[i].y;
			break;
		}
	}
	printf("%d %d",ansx,ansy);
	return 0;
}
