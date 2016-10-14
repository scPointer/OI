#include <cstdio>
#define N 1500005
#define INF 1000000000
inline int RD()
{
	int res,sign;
	char cr;
	while( ((cr=getchar())<'0' || cr>'9') && cr!='-');
	cr=='-'? (sign=-1,res=0): (sign=1,res=cr-'0');
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res*sign;
}
int fa[N];
int eg[N*2],nxt[N*2],head[N],egtot;
int fson[N],bro[N];
int dp[N][2],ws[N][2];
int q[N],stk[N],tops;
long long le[N],ri[N];
int mo;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;nxt[egtot]=head[p1];head[p1]=egtot;
	eg[++egtot]=p1;nxt[egtot]=head[p2];head[p2]=egtot;
}

void setTree(int n)
{
	int r;q[r=1]=1;
	for(int l=1,p;l<=n;l++)
	{
		p=q[l];
		for(int i=head[p],e;i;i=nxt[i])
			if(eg[i]!=fa[p])
			{
				e=eg[i];
				fa[e]=p;
				bro[e]=fson[p];
				fson[p]=e;
				q[++r]=e;
			}
	}
}
int main()
{
	int n=RD();
	for(int i=1;i<n;i++)
		addEdge(RD(),RD());
	mo=RD();
	setTree(n);
	long long cnt=0;
	for(int r=n,p,dmax;r>=1;r--)
	{
		p=q[r];
		if(fson[p]==0){dp[p][0]=0;ws[p][0]=ws[p][1]=dp[p][1]=1;continue;}
		tops=0;
		for(int i=fson[p];i;i=bro[i])
			stk[++tops]=i;
		le[0]=1;ri[tops+1]=1;
		for(int i=1;i<=tops;i++)
			le[i]=(le[i-1]*ws[stk[i]][0])%mo;
		for(int i=tops;i>=1;i--)
			ri[i]= (ri[i+1]*ws[stk[i]][0])%mo;
		ws[p][1]=le[tops]%mo;
		dp[p][1]= p==1?0:1;
		for(int i=1;i<=tops;i++)
			dp[p][1]+=dp[stk[i]][0];
			
		dmax=0;cnt=0;
		for(int i=1,p2;i<=tops;i++)
		{
			p2=stk[i];
			if(dp[p2][1]-dp[p2][0]>dmax)
			{
				dmax=dp[p2][1]-dp[p2][0];
				cnt=(((le[i-1]*ws[p2][1])%mo)*ri[i+1])%mo;
			}
			else if(dp[p2][1]-dp[p2][0]==dmax)
				cnt=(cnt+(((le[i-1]*ws[p2][1])%mo)*ri[i+1])%mo)%mo;
		}
		if(p!=1)dp[p][0]=dp[p][1]-1+dmax;
		else dp[p][0]=dp[p][1]+dmax;
		ws[p][0]=cnt;
	}
	if(dp[1][0]>dp[1][1])
		printf("%d\n%d",dp[1][0],ws[1][0]);
	else if(dp[1][0]<dp[1][1])
		printf("%d\n%d",dp[1][1],ws[1][1]);
	else printf("%d\n%d",dp[1][0],(ws[1][0]+ws[1][1])%mo);
}
