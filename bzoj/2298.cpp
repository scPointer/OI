#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
struct Interv{int l,r,val;}it[N];
inline bool ifdiff(Interv a,Interv b){return a.l!=b.l || a.r!=b.r;}
int itcnt;
int dp[N];
int usotsuki;
int n;
inline int RD(){static int res;scanf("%d",&res);return res;}
bool cmp(Interv a,Interv b)
{
	if(a.r!=b.r) return a.r<b.r;
	else return a.l<b.l;
}
int main()
{
//	freopen("2298.in","r",stdin);
	n=RD();
	for(int i=1,l,r;i<=n;i++)
	{
		l=RD()+1;r=n-RD();
		if(l>r) {usotsuki++;continue;}
		it[++itcnt]=(Interv){l,r,1};
	}
	
	sort(it+1,it+1+itcnt,cmp);
	int cnt=-1,pt=0;
	for(int i=1;i<=itcnt+1;i++)
		if(ifdiff(it[i],it[i-1]))
		{
			it[++cnt]=it[i-1];
			it[cnt].val=Min(i-pt,it[cnt].r-it[cnt].l+1);
			pt=i;
		}
	itcnt=cnt;
	
	for(int i=1;i<=n;i++) dp[i]=-1;
	for(int i=1,tail=0;i<=itcnt;i++)
	{
		Interv& p=it[i];
		while(tail<p.r) dp[++tail]=dp[tail-1];
		dp[p.r]=Max(dp[p.r],dp[p.l-1]+p.val);
	}
	for(int i=1;i<=n;i++) if(dp[i]==-1) dp[i]=dp[i-1];
	usotsuki+= n-usotsuki-dp[n];
	printf("%d",usotsuki);
	return 0;
}
