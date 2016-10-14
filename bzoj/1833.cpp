#include <cstdio>
#define Min(a,b) (a<b?a:b)
long long f[22];
long long p10[22],left[22];
long long d[22];
long long dfs(long long len,long long dig,long long f0,long long final)
{
	if(len==0) return 0;
	if(!f0 && !final && f[len]!=-1) return f[len];
	long long lim= final? d[len]: 9;
	long long res=0;
	for(long long p=0;p<=lim;p++)
		if(f0 && p==0) res+=dfs(len-1,dig,1,0);//有前导零不可能贴上界
		else if(p==dig)
		{
//			if(final) res+=left[len-1]+1+dfs(len-1,dig,0,1);
			if(final && dig==d[len]) res+=left[len-1]+1+dfs(len-1,dig,0,1);
			else res+=p10[len-1]+dfs(len-1,dig,0,0);
		}
		else if(final && p==lim) res+=dfs(len-1,dig,0,1);
		else res+=dfs(len-1,dig,0,0);
	if(!f0 && !final) f[len]=res;
	return res;
}
long long solve(long long lim,long long dig)
{
	for(long long i=0;i<=20;i++) f[i]=-1;//f每次清空
	if(lim<=0) return 0;
	long long len=0;
	while(lim)
	{
		++len;
		d[len]=lim%10;
		left[len]=p10[len-1]*(lim%10)+left[len-1];
		lim/=10;
	}
	return dfs(len,dig,1,1);
}
int main()
{
	p10[0]=1;for(long long i=1;i<=20;i++) p10[i]=p10[i-1]*10;
	long long l,r;
	scanf("%lld%lld",&l,&r);
	for(long long i=0;i<=8;i++)
		printf("%lld ",solve(r,i)-solve(l-1,i));
	printf("%lld\n",solve(r,9)-solve(l-1,9));
}