#include <cstdio>
#include <cmath>
#define PI acos(-1)
#define eps 1e-8
typedef long double ld;
int main()
{
	freopen("HWmahoushaojiu.in","r",stdin);
	freopen("HWmahoushaojiu.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,a,S;scanf("%d%d%d",&n,&a,&S);
		ld nowS=n*a*a/tan(PI/n)/4;
		ld divi=nowS/S;
		if(divi-eps<1) printf("0\n");
		else printf("%d\n",(int)(log10(divi)/(-log10(cos(PI/n)))/2+eps)+1);
	}
}