#include<cstdio>
#define mabs(a) ((a)>=0?(a):(a)*(-1))
#define Max(a,b) (a>b?a:b)
#define N 10001
int n,m;
int f[N],t[N],x[N],y[N],mx[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
		scanf("%d%d%d",&t[i],&x[i],&y[i]);
    for(int i=1;i<=m;i++)
    {
        f[i]=1;
        for(int j=i-1;j>=1;j--)  
        {
            if(mx[j]+1<=f[i])break;
            if(f[j]+1>f[i])
                if(mabs(x[i]-x[j])+mabs(y[i]-y[j])<=t[i]-t[j])
			        f[i]=f[j]+1;
        }
        mx[i]=Max(f[i],mx[i-1]);
    }
    printf("%d",mx[m]);
}
