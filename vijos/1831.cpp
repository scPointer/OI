#include <cstdio>
#include <cassert>
#define N 1030
#define Min(a,b) ((a) < (b)? (a) : (b))
#define Max(a,b) ((a) > (b)? (a) : (b))
#define INF 1500000000
int mtx[N][N],sumpay[N][15];
int n,ns;
int c[N],pay[N],chg[N];
int dp[15][N][N];
bool used[15];
int bits[N];
inline void RD(int& res)
{
	static char cr;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
}
inline int newarray()
{
	static int id=0;
	while(used[id]) id=id%14+1;
	used[id]=1;
	return id;
}
inline void deletearray(int id){used[id]=0;}
void PR(int x,int lim1,int lim2)
{
	for(int i=0;i<lim1;i++)
		for(int j=0;j<lim2;j++)
			printf("dp[%d][%d][%d]: %d\n",x,i,j,dp[x][i][j]);
}
int solve(int ll,int rr)
{
	if(ll==rr)
	{
		int x=newarray(),j,mode=pay[ll]^1,chgmode=mode^1;
		for(int i=0;i<ns;i++)
		{
			dp[x][i][mode]=0;dp[x][i][chgmode]=chg[ll];
			for(j=0;j<n;j++)
				if( ((i&(1<<j)) &&1) ^ chgmode)
					dp[x][i][mode]+=sumpay[ll][j+1];
				else dp[x][i][chgmode]+=sumpay[ll][j+1];
		}
//		PR(x,ns,2);
		return x;
	}
	int lx=solve(ll,(ll+rr)/2);
	int rx=solve((ll+rr)/2+1,rr);
	int son=rr-ll+1,ancestor=ns/son;
	int x=newarray();
	for(int i=0;i<ancestor;i++)
	{
		for(int j=0,mode;j<=son;j++)
		{
			dp[x][i][j]=INF;mode= j>=(son>>1)?0:1;
			for(int k=Max(j-(son>>1),0);k<=Min(son>>1,j);k++)
				dp[x][i][j]=Min(dp[lx][(i<<1)|mode][k]+dp[rx][(i<<1)|mode][j-k],dp[x][i][j]);
		}
	}
	deletearray(lx);
	deletearray(rx);
	return x;
}
void Sumpay(int p,int floor,int ll,int rr)
{
	if(!floor) return;
	int mid=(ll+rr)>>1;
	if(p<=mid)
	{
		for(int i=mid+1;i<=rr;i++)
			sumpay[p][floor]+=mtx[p][i];
		Sumpay(p,floor-1,ll,mid);
	}
	else
	{
		for(int i=ll;i<=mid;i++)
			sumpay[p][floor]+=mtx[p][i];
		Sumpay(p,floor-1,mid+1,rr);
	}
}
int main()
{
	RD(n);ns=1<<n;
	for(int i=1;i<=ns;i++) RD(pay[i]);
	for(int i=1;i<=ns;i++) RD(chg[i]);
	for(int i=1;i<ns;i++)
		for(int j=i+1;j<=ns;j++)
			RD(mtx[i][j]),mtx[j][i]=mtx[i][j];
	for(int i=0;i<n;i++) bits[1<<i]=i+1;
	for(int i=1;i<=ns;i++)
		Sumpay(i,n,1,ns);
	int root=solve(1,ns),ans=INF;
	for(int i=0;i<=ns;i++) ans=Min(dp[root][0][i],ans);
	printf("%d",ans);
	return 0;
}
