#include <cstdio>
int fac[100],inv[100];
void pre()
{
	int mo=10007;
	fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(int j=2;j<mo;j++)
		fac[j]=fac[j-1]*j%mo,
		inv[j]=inv[mo%j]*(mo-mo/j)%mo;
	for(int j=2;j<mo;j++)
		inv[j]=inv[j]*inv[j-1]%mo;
}
int main()
{
	pre();
}