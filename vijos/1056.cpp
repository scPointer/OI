#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define MAXN 201
#define swap(a,b) {int sw;sw=a;a=b;b=sw;}
long long area[MAXN][MAXN];
int xlen[MAXN],ylen[MAXN];
bool cover[MAXN][MAXN];
int fx[MAXN],fy[MAXN];
int fxs[MAXN],fys[MAXN];
map<int,int> mmx,mmy;
//map<int,int>::iterator find;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d %d %d",&fx[i],&fy[i],&fx[i+n],&fy[i+n]);
//		if(fx[i]>fx[i+n])
//			swap(fx[i],fx[i+n]);
//		if(fy[i]>fy[i+n])
//			swap(fy[i],fy[i+n]);
	}
	for(int i=1;i<=n*2;i++)
	{
		fxs[i]=fx[i];
		fys[i]=fy[i];
	}
	sort(fxs+1,fxs+1+n*2);
	sort(fys+1,fys+1+n*2);
	int xtop=0,ytop=0;
	for(int i=1;i<=n*2;i++)
		if(i==1||fxs[i]!=fxs[i-1])
		{
			mmx[fxs[i]]=++xtop;
			xlen[xtop]=fxs[i];
		}
	for(int i=1;i<=n*2;i++)
		if(i==1||fys[i]!=fys[i-1])
		{
			mmy[fys[i]]=++ytop;
			ylen[ytop]=fys[i];
		}
	for(int i=1;i<=xtop-1;i++)
		for(int j=1;j<=ytop-1;j++)
			area[i][j]=(long long)(xlen[i+1]-xlen[i])*(long long)(ylen[j+1]-ylen[j]);
	for(int i=1;i<=n;i++)
	{
		int stx=mmx[fx[i]],edx=mmx[fx[i+n]];
		int sty=mmy[fy[i]],edy=mmy[fy[i+n]];
		for(int j=stx;j<edx;j++)
			for(int k=sty;k<edy;k++)
				cover[j][k]=true;

	}
	long long ans=0;
	for(int i=1;i<=xtop;i++)
		for(int j=1;j<=ytop;j++)
			if(cover[i][j]==true)
				ans+=area[i][j];
	printf("%I64d",ans);
	return 0;
}
