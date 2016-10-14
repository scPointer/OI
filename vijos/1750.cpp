#include <cstdio>
#include <algorithm>
char s__[1<<18],*s_s,*s_t;
inline int gchar()
{
	if(s_s==s_t) s_s=s__,s_t=s_s+fread(s__,1,(1<<18)-5,stdin);
	return *s_s++;
}
inline int RD()
{
	int res;
	char cr;
	while( (cr=gchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=gchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
#define N 1005
struct Node{
	int x,y;
	long long val;
}nd[N*N];
inline bool cmp(const Node& a,const Node& b)
{
	if(a.val!=b.val) return a.val<b.val;
	else if(a.x!=b.x) return a.x<b.x;
	else return a.y<b.y;
}
int mtx[N][N];
int mn[N][N];
long long sum[N][N];
int stk[N],pos[N],ll,rr;
bool rem[N][N];
int ans[N*N],anscnt;
int main()
{
	int n,m,a,b;n=RD();m=RD();a=RD();b=RD();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			mtx[i][j]=RD();
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			sum[i][j]=sum[i][j+1]+mtx[i][j];
	for(int i=n;i>=1;i--)
		for(int j=1;j<=m-b+1;j++)
			sum[i][j]-=sum[i][j+b];
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			sum[i][j]=sum[i+1][j]+sum[i][j];
	for(int i=1;i<=n-a+1;i++)
		for(int j=m;j>=1;j--)
			sum[i][j]-=sum[i+a][j];
	for(int i=1;i<=n;i++)
	{
		ll=1,rr=0;
		for(int j=1;j<=b;j++)
		{
			while(ll<=rr && mtx[i][j]<stk[rr]) rr--;
			stk[++rr]=mtx[i][j];pos[rr]=j;
		}
		mn[i][1]=stk[ll];
		for(int j=b+1;j<=m;j++)
		{
			if(pos[ll]<=j-b) ll++;
			while(ll<=rr && mtx[i][j]<stk[rr]) rr--;
			stk[++rr]=mtx[i][j];pos[rr]=j;
			mn[i][j-b+1]=stk[ll];
		}
	}
	for(int j=1;j<=m;j++)
	{
		ll=1,rr=0;
		for(int i=1;i<=a;i++)
		{
			while(ll<=rr && mn[i][j]<stk[rr]) rr--;
			stk[++rr]=mn[i][j];pos[rr]=i;
		}
		mtx[1][j]=stk[ll];
		for(int i=a+1;i<=n;i++)
		{
			if(pos[ll]<=i-a) ll++;
			while(ll<=rr && mn[i][j]<stk[rr]) rr--;
			stk[++rr]=mn[i][j];pos[rr]=i;
			mtx[i-a+1][j]=stk[ll];
		}
	}
	int cnt=0;
	for(int i=1;i<=n-a+1;i++)
		for(int j=1;j<=m-b+1;j++)
			nd[++cnt]=(Node){i,j,sum[i][j]-(long long)mtx[i][j]*a*b};
	std::sort(nd+1,nd+1+cnt,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int x=nd[i].x,y=nd[i].y;
		if(!rem[x][y] && !rem[x+a-1][y+b-1] && !rem[x+a-1][y] && !rem[x][y+b-1])
		{
			ans[++anscnt]=i;
			for(int i=x;i<=x+a-1;i++)
				for(int j=y;j<=y+b-1;j++)
					rem[i][j]=1;
		}
	}
	printf("%d\n",anscnt);
	for(int i=1;i<=anscnt;i++)
		printf("%d %d %I64d\n",nd[ans[i]].x,nd[ans[i]].y,nd[ans[i]].val);
}