#include <cstdio>
#define setM(m,a,b,c,d) (m.x[0][0]=a,m.x[0][1]=b,m.x[1][0]=c,m.x[1][1]=d)
#define copyM(a,b) setM(a,b.x[0][0],b.x[0][1],b.x[1][0],b.x[1][1])
long long mo;
struct Matrix{long long x[2][2];}ans,mtx;
inline long long plus(long long a,long long b){return (a+b)%mo;}
inline long long mult(long long a,long long b)
{
	a%=mo;b%=mo;
	long long res=0;
	while(b)
	{
		if(b&1) res=(res+a)%mo;
		a=(a+a)%mo;
		b>>=1;
	}
	return res;
}
Matrix MatrixMult(Matrix b,Matrix c)
{
	Matrix a;
	setM(a,0,0,0,0);
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				a.x[i][j]=plus(a.x[i][j],mult(b.x[i][k],c.x[k][j]));
	return a;
}
int main()
{
	long long a0,c0,x0,n,out_mo;
	scanf("%lld%lld%lld%lld%lld%lld",&mo,&a0,&c0,&x0,&n,&out_mo);
	setM(mtx,1,0,c0,a0);
	setM(ans,1,0,0,1);
	while(n)
	{
		if(n&1) ans=MatrixMult(ans,mtx);
		mtx=MatrixMult(mtx,mtx);
		n>>=1;
	}
	long long xn=plus(ans.x[1][0],mult(ans.x[1][1],x0))%out_mo;
	printf("%lld",xn);
}