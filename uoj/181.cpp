#include <cstdio>
#include <algorithm>
using namespace std;
#define N 12
#define MO 998244353
int n,m;
int gl[N][N];
int dir[N][N];
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			gl[i][j]=5000;
	for(int i=1;i<=n;i++)
		dir[n+1][i]=1;
	for(int i=1;i<=m;i++)
	{
		int p1,p2,v;
		scanf("%d%d%d",&p1,&p2,&v);
		gl[p1][p2]=v;
	}
}
int stk[N],stktop;
int vist[N],mlink[N],scc[N];
int nowtime,sccnum;
void dfs(int p)
{
    vist[p]=mlink[p]=++nowtime;
    stk[++stktop]=p;
    for(int i=1;i<=n;i++)
    {
        if(!dir[p][i] ||i==p) continue;
        if(vist[i]==0)
        {
            dfs(i);
            mlink[p]=min(mlink[p],mlink[i]);
        }
        else if(scc[i]==0)
            mlink[p]=min(mlink[p],mlink[i]);
    }
	if(vist[p]==mlink[p])
	{
		sccnum++;
		int r;
		do
		{
			r=stk[stktop--];
			scc[r]=sccnum;
		}while(r!=p);
	}
}
int main()
{
	init();
	long long possible,ans=0;
	for(int sta=(1<<(((n-1)*n)/2))-1;sta>-1;sta--)
	{
		int tot=0;possible=1;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				dir[i][j]=(sta&(1<<tot))&&1;
				dir[j][i]=1-dir[i][j];
				tot++;
				if(dir[i][j])possible=(possible*gl[i][j])%MO;
				else possible=(possible*(10000-gl[i][j]))%MO;
				possible=(possible*10000)%MO;
			}
		for(int i=1;i<=n+1;i++)
			vist[i]=mlink[i]=scc[i]=0;
		nowtime=sccnum=0;
		dfs(n+1);
		sccnum--;
		ans=(ans+possible*sccnum)%MO;
	}
	printf("%lld",ans);
	return 0;
}
