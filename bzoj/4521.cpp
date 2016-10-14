#include <cstdio>
#include <cstring>
//#include <ctime>
long long f[13][11][3][2];
long long d[15],left[15],p10[15];
int totlen;
long long g[15][3],gd[15];
long long inlaw(int len,int if48,int final)
{
	if(len==0) return 1;
//	WA3: if(len==0) return 0;
	if(!final && g[len][if48]!=-1)
		return g[len][if48];
	int lim= final? gd[len]: 9;
	long long res=0;
	for(int i=0;i<=lim;i++)
		if(i==4)
		{
			if(if48!=2)
				res+=inlaw(len-1,1,final&&i==gd[len]);
		}
		else if(i==8)
		{
			if(if48!=1)
				res+=inlaw(len-1,2,final&&i==gd[len]);
		}
		else res+=inlaw(len-1,if48,final&&i==gd[len]);
	if(!final && g[len][if48]==-1)
		g[len][if48]=res;
	return res;
}
long long set(long long lim,int if48)
{
	int len=0;
	while(lim)
	{
		++len;
		gd[len]=lim%10;
		lim/=10;
	}
	return inlaw(len,if48,1);
}
long long dfs(int len,int last,int if48,int same,int final)
{
	if(len==0) return 0;
	if(!final && f[len][last][if48][same]!=-1) 
		return f[len][last][if48][same];
	int lim= final? d[len]: 9;
	long long res=0;
	for(int i=0;i<=lim;i++)
		if(len==totlen && i==0) continue;
		else if(i==last && same==1)
		{
//			WA2: res+= final? set(left[len-1]+1,if48): set(p10[len-1],if48);
//			WA4: res+= final? set(left[len-1],if48): set(p10[len-1]-1,if48);
			res+= final&&i==d[len]? set(left[len-1],if48): set(p10[len-1]-1,if48);
		}
		else if(i==4)
		{
			if(if48!=2)
				res+=dfs(len-1,4,1,last==4,final&&i==d[len]);
		}
		else if(i==8)
		{
			if(if48!=1)
				res+=dfs(len-1,8,2,last==8,final&&i==d[len]);
		}
		else res+=dfs(len-1,i,if48,last==i,final&&i==d[len]);
	if(!final &&f[len][last][if48][same]==-1)
		f[len][last][if48][same]=res;
	return res;
}
long long solve(long long lim)
{
	if(lim<10000000000ll) return 0;
//	memset(f,-1,sizeof(f));
	int len=0;
	while(lim)
	{
		++len;
		left[len]= (d[len]=lim%10)*p10[len-1]+left[len-1];
		lim/=10;
	}
	totlen=len;
	return dfs(len,-1,0,0,1);
}
int main()
{
//	int c1=clock();
//	freopen("4521.in","r",stdin);
	
	memset(g,-1,sizeof(g));memset(f,-1,sizeof(f));
	p10[0]=1; for(int i=1;i<=14;i++) p10[i]=p10[i-1]*10;
	long long l,r;
//	WA1: lost previous
//	int T; scanf("%d",&T);
//	while(T--){
	scanf("%lld%lld",&l,&r);
	printf("%lld",solve(r)-solve(l-1));
//	}
	
//	int c2=clock();
//	printf("time %d\n",c2-c1);
}