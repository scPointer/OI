#include <cstdio>
#include <cstring>
#define N 105
#define dMin(a,b) ((a)>(b)?(a)=(b):0)
long long hash[N],exp27[N];
int dp[N][N];
char s[N];
int bts[N];
inline long long gethash(int l,int r){return hash[r]-hash[l-1]*exp27[r-l+1];}
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	hash[0]=0;exp27[0]=1;
	for(int i=1;i<=len;i++)
	{
		hash[i]=hash[i-1]*27+(s[i-1]-'A'+1);
		exp27[i]=exp27[i-1]*27;
	}
	for(int i=1;i<=len;i++) bts[i]=bts[i/10]+1;
	for(int i=1;i<=len;i++) dp[i][i]=1;
	for(int k=2;k<=len;k++)
		for(int i=1,j=k; i<=len-k+1; i++,j++)
		{
			dp[i][j]=k;
			for(int l=i;l<=j-1;l++)
				dMin(dp[i][j],dp[i][l]+dp[l+1][j]);
			for(int l=1;l<=k/2;l++)
				if(k%l==0 && gethash(i,j-l)==gethash(i+l,j))
						dMin(dp[i][j],dp[i][i+l-1]+2+bts[k/l]);
		}
	printf("%d",dp[1][len]);
}
