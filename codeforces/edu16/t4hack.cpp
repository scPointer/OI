#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
using namespace std;
#define rep(i,n) for(int i = 0; i < n; ++i)
#define Rep(i,n) for(int i = 1; i <= n; ++i)
#define lowbit(x) ((x)&(-x))
//#pragma comment(linker,"/STACK:1024000000,1024000000")
#define eps 1e-6
#define sqr(x) ((x)*(x))
#define pb(x) push_back(x)
typedef long long ll;
typedef long double ld;
template<class T>inline void rread(T&num){
	num=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	num*=f;
}
const int inf = 2e9, mod = 1e9 + 7;
const int maxn =2e7 +10;
const ld PI = acos(-1.0);
ll gcd (ll a, ll b)
{return ( a ? gcd(b%a, a) : b );}
ll power(ll a, ll n)
{ll p = 1;while (n > 0) {if(n%2) {p = p * a;} n >>= 1; a *= a;} return p;}
ll power(ll a, ll n, ll mod)
{ll p = 1;while (n > 0) {if(n%2) {p = p * a; p %= mod;} n >>= 1; a *= a; a %= mod;} return p % mod;}
//head

int n,m;
ll x,y;
ll dp[maxn];
int main()
{
    while(~scanf("%d%lld%lld",&n,&x,&y))
    {
        for(int i=1;i<=n+n;i++)
            dp[i]=-1;
        dp[0]=0;
        for(int i=1;i<=n;i++)
        {
            if(dp[i]==-1)
            dp[i]=dp[i-1]+x;
        else dp[i]=min(dp[i],dp[i-1]+x);
            if(dp[i+1]!=-1)
            dp[i]=min(dp[i],dp[i+1]+x);
            if((ll)i*x>=y)
            dp[2*i]=dp[i]+y;
           // cout<<dp[i]<<endl;
        }
        cout<<dp[n]<<endl;

    }


    return 0;
}