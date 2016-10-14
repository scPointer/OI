#include <cstdio>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int map[129][129];
int fr[129][129];
int n,d;
void setmap(int x,int y,int k0)
{
	for(int i=max(x-d,0);i<=min(x+d,128);i++)
		for(int j=max(y-d,0);j<=min(y+d,128);j++)
			map[i][j]+=k0;
}
int main()
{
//	freopen("wireless.in","r",stdin);
//	freopen("wireless.out","w",stdout);
	scanf("%d",&d);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x0,y0,k0;
		scanf("%d%d%d",&x0,&y0,&k0);
		setmap(x0,y0,k0);
	}
	int maxcover=0,ans=0;
	for(int i=0;i<=128;i++)
		for(int j=0;j<=128;j++)
		{
			int ret=map[i][j];
			if(ret==maxcover) ans++;
			else if(ret>maxcover)
			{
				maxcover=ret;
				ans=1;
			}
		}
	printf("%d %d",ans,maxcover);
	return 0;
}
