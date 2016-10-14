#include <iostream>
using namespace std;
#define MOD 100000000
int n;
int map[13];
int dp[12][1<<12];
bool inrule[1<<12];
int setdata(int n)
{
	int i4=1,i5=1,seti;
	for(int i=0;i<12;i++)
	{
		i5=1;
		for(int j=0;j<11;j++)
		{
			if(i4*i5>n){map[i]=j-1;break;}
			i5*=5;
		}
		i4*=4;
		if(i4<=n) seti=i+1;
		else break;
	}
	return seti;
}
int main()
{
	cin>>n;
	int hs=setdata(n);
	for(int i=0;i<1<<(map[0]+1);i++)
	{
		int stt=i;
		bool flag=0;
		while(stt>0)
		{
			if(stt%4==3){flag=1;break;}
			stt>>=1;
		}
		if(flag==0) dp[0][i]=1;
	}
	
	for(int i=1;i<=hs;i++)
		for(int j=0;j<1<<(map[i]+1);j++)
		{
			if(dp[0][j]==0) continue;
			for(int k=0;k<1<<(map[i-1]+1);k++)
				if(dp[0][k]!=0&&((j&k)==0))
					dp[i][j]=(dp[i][j]+dp[i-1][k])%MOD;
		}
	int ans=0;
	for(int i=0;i<1<<(map[hs]+1);i++)
		ans=(ans+dp[hs][i])%MOD;
	printf("%d",ans);
	return 0;
}
