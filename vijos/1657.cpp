#include <cstdio>
#include <cstring>
#define MAX(a,b) (a>b?a:b)
#define MAXN 185
#define CHARS 2000
int dist[MAXN][MAXN];//distance from one kid to another
int mtx[MAXN][MAXN];//adjacency matrix, from one doll to a kid
int att[MAXN],wer[MAXN];//attraction;where the i(th) doll is

bool vis[MAXN];
int match[MAXN],limit;

char name[MAXN][CHARS];
int n;
void initialization()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&att[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&wer[i]);
	for(int i=1;i<=n;i++)
		scanf("%s",name[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&dist[i][j]);
//			if(i==j) dist[i][j]=0;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
}
void SetAdjacencyMatrix()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mtx[i][j]=att[i]-dist[wer[i]][j];
}
bool dfs(int p)
{
	for(int i=1;i<=n;i++)
		if(mtx[p][i]<=limit && vis[i]==0)
		{
			vis[i]=1;
			if(match[i]==0 || dfs(match[i])==1)
			{
				match[i]=p;
				return 1;
			}
		}
	return 0;
}
bool check()
{
	memset(match,0,sizeof(match));
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(dfs(i)==0) return 0;
	}
	return 1;
}
int main()
{
	initialization();
	SetAdjacencyMatrix();
	int l=-50000001,r=50000000;
	while(l<r-1)
	{
		limit=(l+r)/2;
		if(check()==1) r=limit;
		else l=limit;
	}
	printf("%d\n",r);
	for(int i=1;i<=n;i++)
		printf("%s\n",name[match[i]]);
	return 0;
}
