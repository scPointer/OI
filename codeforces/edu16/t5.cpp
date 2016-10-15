#include <cstdio>
#include <iostream>
using namespace std;
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define INF 10000000000000000ll
long long n,x,y;
long long check(long long k,long long p)
{
	long long cnt=0;
	for(int i=1;i<=k;i++)
	{
		if(p&1) cnt++;
		p>>=1;
	}
	return k*y+(cnt+p)*x;
}
long long f[10000005];
long long dfs(int p,int last)
{
	if(p==0) return 0;
	if(f[p]>0) return f[p];
	long long mn,res;
	mn=INF;
	if(!(p&1)) 
	{
		res=dfs(p>>1,0)+y;
		mn=Min(mn,res);
	}
	if(last==0 && last>=0)
	{
		res=dfs(p+1,1)+x;
		mn=Min(mn,res);
	}
	if(last==0 || last==-1)
	{
		res=dfs(p-1,-1)+x;
		mn=Min(mn,res);
	}
	if(mn<INF) return f[p]=mn;
	return mn;
}
int main()
{
	cin>>n>>x>>y;
	f[1]=x;
	for(int i=2;i<=n;i++)
	{
		f[i]=0;
		dfs(i,0);
	}
	
	cout<<f[n];
}