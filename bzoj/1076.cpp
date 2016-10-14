#include <cstdio>
#define N 16
#define K 105
#define Max(a,b) (a>b?a:b)
int need[N];
double dp[2][1<<N];
int score[N];
inline int RD(){static int res;scanf("%d",&res);return res;}
int main()
{
    int k,n;
    k=RD();n=RD();
    for(int i=1,p;i<=n;i++)
    {
        score[i]=RD();
        while((p=RD())!=0)
            need[i]|=1<<(p-1);
    }
    int x=0;
    for(int i=1;i<=k;i++)
    {
        x^=1;
        for(int j=0;j<(1<<n);j++)
            dp[x][j]=0;
        for(int j=0;j<(1<<n);j++)
		{
            for(int k=1;k<=n;k++)
			{
                if((need[k]&j)==need[k])
                    dp[x][j]+=(Max(dp[x^1][j|(1<<(k-1))]+score[k],dp[x^1][j]));
                else dp[x][j]+=dp[x^1][j];
            }
			dp[x][j]/=n;
		}
    }
    printf("%.06lf",dp[x][0]);
}