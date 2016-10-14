#include <cstdio>
#include <cstring>
#define mo 7528443412579576937ull
typedef unsigned long long ll;
inline ll mult(ll a,ll b)
{
	ll res=0; a%=mo;b%=mo;
	while(b)
	{
		if(b&1) res=(res+a)%mo;
		a=(a+a)%mo;
		b>>=1;
	}
	return res;
}
inline ll plus(ll a,ll b){return (a+b)%mo;}
inline ll minus(ll a,ll b){return (a-b+mo)%mo;}
struct Matrix{
	ll a[2][2];
	Matrix(){memset(a,0,sizeof(a));}
};
Matrix mult(Matrix x,Matrix y)
{
	Matrix c;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				c.a[i][k]=plus(c.a[i][k],mult(x.a[i][j],y.a[j][k]));
	return c;
}
int  main()
{
	ll b,d,n,setn;
	scanf("%lld%lld%lld",&b,&d,&n);setn=n;
	if(n==0){printf("1");return 0;}
	Matrix m,ans;
	m.a[0][0]=0;m.a[0][1]=1;m.a[1][0]=minus(d,mult(b,b))/4ull;m.a[1][1]=b;
	bool flag=0;
	while(n)
	{
		if(n&1)
			flag? ans=mult(ans,m): ans=m,flag=1;
		m=mult(m,m);
		n>>=1;
	}
	ll an=plus(mult(ans.a[0][0],2),mult(ans.a[0][1],b));
	if((d!=mult(b,b))&&setn%2==0) an=minus(an,1);
	printf("%lld",an);
}