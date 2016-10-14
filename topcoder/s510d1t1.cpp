#include <cstdio>
#include <cstring>
#define N 20
int bts[N];
long long f[N][2];
class TheAlmostLuckyNumbersDivOne{
	public:
	long long dfs(int now,int pre0,int upp,int unl){
		if(now==0) return 1;
		if(upp==0 && f[now][unl]!=-1) return f[now][unl];
		long long res=0;
		int k=upp? bts[now]: 9;
		for(int i=0;i<=k;i++)
		{
			if(pre0 && i==0)
				res+=dfs(now-1,pre0,upp&&i==bts[now],unl);
			else if(i!=4 && i!=7 && unl==0)
				res+=dfs(now-1,0,upp&&i==bts[now],1);
			else if(i==4 || i==7)
				res+=dfs(now-1,0,upp&&i==bts[now],unl);
		}
		if(upp==0&&pre0==0) f[now][unl]=res;
		return res;
	}
	long long solve(long long a){
		memset(f,-1,sizeof(f));
		int k=0;
		while(a)
		{
			bts[++k]=a%10;
			a/=10;
		}
		return dfs(k,1,1,0);
	}
	long long find(long long a, long long b){
		return solve(b)-solve(a-1);
	}
};
TheAlmostLuckyNumbersDivOne obj;
int main()
{
	long long a,b; scanf("%lld%lld",&a,&b);
	printf("%lld",obj.find(a,b));
}
