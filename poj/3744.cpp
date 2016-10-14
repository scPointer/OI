#include <cstdio>
#include <algorithm>
using namespace std;
int sc[12];
struct Matrix{
	double a[2][2];
	Matrix operator*(Matrix ot)
	{
		Matrix c;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				c.a[i][j]=0;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					c.a[i][j]+=a[i][k]*ot.a[k][j];
		return c;
	}
}mtx[30];
Matrix getone()
{
	Matrix c;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			c.a[i][j]= i==j? 1:0;
	return c;
}
Matrix pow(int p)
{
	Matrix res=getone();
	int cnt=0;
	while(p)
	{
		if(p&1) res=res*mtx[cnt];
		p>>=1;cnt++;
	}
	return res;
}
void solve(int n,double p)
{
	mtx[0].a[0][0]=0;mtx[0].a[0][1]=1;
	mtx[0].a[1][0]=1-p;mtx[0].a[1][1]=p;
	for(int i=1,j=2;j<=sc[n];i++,j<<=1)
		mtx[i]=mtx[i-1]*mtx[i-1];
	double ans=1;
	for(int i=1;i<=n;i++)
	{
		Matrix temp=pow(sc[i]-sc[i-1]-1);
		ans*=(1-temp.a[1][1]);
	}
	printf("%.7lf\n",ans);
}
int main()
{
	int n;
	double p;
	while(scanf("%d",&n)!=EOF)
	{
		scanf("%lf",&p);
		for(int i=1;i<=n;i++)
			scanf("%d",&sc[i]);
		sort(sc+1,sc+1+n);
		solve(n,p);
	}
}