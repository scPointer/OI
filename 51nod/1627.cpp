#include <cstdio>
#define Swap(a,b) {int _t=a;a=b;b=_t;}
#define N 200005
#define mo 1000000007
long long fac[N],inv[N];
void init(int lim)
{
	fac[0]=fac[1]=1;
	for(int i=2;i<=lim;i++) fac[i]=fac[i-1]*i%mo;
	inv[0]=inv[1]=1;
	for(int i=2;i<=lim;i++)
		inv[i]=inv[mo%i]*(mo-mo/i)%mo;
	for(int i=2;i<=lim;i++)
		inv[i]=(inv[i-1]*inv[i])%mo;
}
int C(int n,int m){return (fac[n]*inv[m]%mo)*inv[n-m]%mo;}
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	if(n<m) Swap(n,m);
	init(n+m);
	if(m==1) n==1? puts("1"): puts("0");
	else printf("%d",C(n+m-4,m-2));
}