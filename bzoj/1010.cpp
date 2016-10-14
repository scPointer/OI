#include <cstdio>
#define N 50005
long long sum[N],x[N],y[N],dp[N];
long long L;
long long q[N];
inline double getk(int p1,int p2)
{return (double)(y[p1]-y[p2])/(sum[p1]-sum[p2]);}
inline double needk(int p){return (double)sum[p]*2;}
inline long long calc(int p1,int p2){return dp[p2]+(sum[p1]-sum[p2]-L)*(sum[p1]-sum[p2]-L);}
inline long long calcy(int p){return dp[p]+2*sum[p]*L+sum[p]*sum[p];}
int main()
{
	long long n,p;
	scanf("%lld%lld",&n,&L);L+=1;
	sum[0]=0;dp[0]=0;x[0]=0;y[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&p);
		sum[i]=sum[i-1]+p;
	}
	for(int i=1;i<=n;i++) sum[i]+=i;
	int l,r;
	q[l=r=1]=0;
	for(int i=1;i<=n;i++)
	{
//		printf("top%d k%lf need%lf\n",stk[top],getk(stk[top],stk[top-1])+1e-10,needk(i));
		while(l<r && getk(q[l],q[l+1])<needk(i)) l++;
		dp[i]=calc(i,q[l]);
		y[i]=calcy(i);
		while(l<r && getk(q[r],q[r-1])>getk(q[r],i)) r--;
		q[++r]=i;
	}
	printf("%lld",dp[n]);
}
