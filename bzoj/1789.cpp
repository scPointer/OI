#include <cstdio>
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define N 55
int len[3];
char val[3][N];
long long hash[3][N];
int lcp[3];
int getlcp(int p1,int p2)
{
    for(int i=Min(len[p1],len[p2])-1;i>=0;i--)
        if(hash[p1][i]==hash[p2][i]) return i+1;
    return 0;
}
int solve(int p1,int p2,int p3)
{
    int length=Max(lcp[p2],lcp[p3]);
    int rez=len[p1]-length;
    rez+=len[p2]-lcp[p3] + length-lcp[p3];
    rez+=len[p3]-lcp[p2] + length-lcp[p2];
    return rez;
}
int main()
{
    for(int i=0;i<3;i++)
    {
        scanf("%d",&len[i]);
        scanf("%s",val[i]);
        hash[i][0]=(long long)(val[i][0]-'A'+1);
        for(int j=1;j<len[i];j++)
            hash[i][j]=hash[i][j-1]*27+val[i][j]-'A'+1;
//            printf("hash[%d][%d]=%lld\n",i,j,hash[i][j]);
    }
    int ans[3];
    lcp[0]=getlcp(1,2);lcp[1]=getlcp(0,2);lcp[2]=getlcp(0,1);
    ans[0]=solve(0,1,2);ans[1]=solve(1,0,2);ans[2]=solve(2,0,1);
//    printf("lcp= %d %d %d\n",lcp[0],lcp[1],lcp[2]);
    printf("%d",Min(Min(ans[0],ans[1]),ans[2]));
    return 0;
}
