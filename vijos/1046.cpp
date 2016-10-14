#include <cstdio>
#define MAXN 101
#define MAXINT 500000000
#define MIN(a,b) ((a)<(b)?(a):(b))
int n,m;
int fl[MAXN][MAXN];
int ed[MAXN][MAXN];
int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j) ed[i][j]=fl[i][j]=MAXINT;
		for(int i=1;i<=m;i++)
		{
			int p1,p2,w;
			scanf("%d%d%d",&p1,&p2,&w);
			if(ed[p1][p2]>w)
				ed[p2][p1]=ed[p1][p2]=fl[p2][p1]=fl[p1][p2]=w;
		}
		int ans=MAXINT;
		for(int k=1;k<=n;k++)
		{
			for(int i=1;i<=k-1;i++)
				for(int j=i+1;j<=k-1;j++)
					ans=MIN(ans,fl[i][j]+ed[i][k]+ed[j][k]);
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					fl[i][j]=MIN(fl[i][j],fl[i][k]+fl[k][j]);
		}
		if(ans<MAXINT) printf("%d\n",ans);
		else printf("No solution.\n");
	}
	return 0;
}
