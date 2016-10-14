#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdio>
#define M 230
using namespace std;
typedef long double ld;
int n,m;
ld p[M],d[M],f[M][M];
void Initialize()
{
    memset(f,0,sizeof f);
}
int main()
{
    int T,i,j;scanf("%d",&T);
    for(;T;T--)
    {
        Initialize();
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            double x,y;
            scanf("%lf%lf",&x,&y);
            p[i]=x;d[i]=y;
        }
        f[0][m]=1;
        ld ans=0;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                f[i][j]=f[i-1][j]*pow(1-p[i-1],j)+f[i-1][j+1]*(1-pow(1-p[i-1],j+1));
                ans+=f[i][j]*(1-pow(1-p[i],j))*d[i];
//				printf("%.10lf\n",(double)ans);
            }
        printf("%.10lf\n",(double)ans);
    }
    return 0;
}