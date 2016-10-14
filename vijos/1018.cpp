#include <cstdio>
#define INF (1<<25)
#define N 105
#define sqr(a) ((a)*(a))
#define dis(i,j) (sqr(cdy[i][0]-cdx[j][0])+sqr(cdy[i][1]-cdx[j][1]))
#define dMin(a,b) ((a) < (b)? 0:(a) = (b))
int n,m,dd,ans,cnt;
int cdx[N][2],cdy[N][2];
int reach[N][N];
int tail[N],dp[N];
int e[N*N],head[N],next[N*N],etot;
bool used[N];
void init()
{
	scanf("%d%d%d",&n,&m,&dd);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&cdx[i][0],&cdx[i][1]);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&cdy[i][0],&cdy[i][1]);
	for(int i=1;i<=n;i++) tail[i]=INF;
	ans=n;
}
inline void addline(int l,int r){dMin(tail[r],l);}
void DP()
{
	for(int i=1;i<=n;i++) dp[i]=INF;
	for(int i=1;i<=n;i++)
		if(tail[i]==INF) dp[i]=dp[i-1]+1;
		else
		{
			for(int j=tail[i]-1;j<i;j++) dMin(dp[i],dp[j]+1);
			for(int j=i-1;j>0;j--) dMin(dp[j],dp[i]);	
		}
}
void addedge(int p,int q){e[++etot]=q;next[etot]=head[p];head[p]=etot;}
void DFS(int p)
{
	if(p<=0) {dMin(ans,cnt);return;}
	if(dp[p]+cnt>=ans) return;
	for(int i=head[p];i;i=next[i])
		if(!used[e[i]])
		{
			used[e[i]]=1;cnt++;
			DFS(reach[e[i]][p]-1);
			used[e[i]]=0;cnt--;
		}
}
int main()
{
	init();
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(dis(i,j)<=dd*dd)
			{
				reach[i][j]= reach[i][j-1]?reach[i][j-1]:j;
				addedge(j,i);
			}
	for(int i=1;i<=m;i++)
		for(int j=n;j;j--)
		{
			while(j && !reach[i][j]) j--;
			if(!j) break;
			addline(reach[i][j],j);
			j=reach[i][j];
		}
	DP();
	if(m<=15) DFS(n);
	else ans=dp[n];
	printf("%d",ans);
}