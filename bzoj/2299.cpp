#include <cstdio>
#define check(a,b) ((a)%d==0 && (b)%d==0)
inline int RD(){static int res;scanf("%d",&res);return res;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main()
{
	for(long long T=RD(),a,b,x,y,d;T;T--)
	{
		a=RD();b=RD();x=RD();y=RD();
		d=gcd(2*a,2*b);
		if(check(x,y)|| check(x+a,y+b) ||check(x+b,y+a) || check(x+a+b,y+a+b))
			printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
