#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 301
int dset[MAXN];
struct road
{
	int x,y,c;
}r[MAXN*MAXN];
inline bool cmp(road a,road b)
{
	return a.c<b.c;
}
int find(int p)
{
	if(dset[p]!=p) dset[p]=find(dset[p]);
	return dset[p];
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		dset[i]=i;
	for(int i=1;i<=m;i++)
		cin>>r[i].x>>r[i].y>>r[i].c;
	sort(r+1,r+1+m,cmp);
	int cp=0;//the points that have connected
	for(int i=1;i<=m;i++)
	{
		int a=find(r[i].x),b=find(r[i].y);
		if(a!=b)
		{
			dset[a]=b;
			cp++;
		}
		if(cp==n-1)
		{
			cout<<cp<<' '<<r[i].c;
			break;
		}
	}
	return 0;
}
