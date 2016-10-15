#include <iostream>     
#include <cstdio>     
#include <cstdlib>     
#include <cstring>
#define Max(a,b) (a>b?a:b)
using namespace std;    
long long x, y, t;    
long long egcd(long long a, long long b)     
{    
	if (b==0)       
	{    
		x=1;          
		y=0;       
		return a;       
	}    
	else     
	{    
		long long e=egcd(b,a % b);     
		t=x;     
		x=y;    
		y=t-a/b*y;       
		return e;       
	}    
}
long long check(long long lim,long long k,long long b)
{
	long long l=-1,r=5000000001ll,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(k*mid+b<=lim) l=mid;
		else r=mid;
	}
	return l;
}
long long rep(long long p,long long m,long long lim)
{
	long long l=-50000000001ll,r=5000000001ll,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(m*mid+p>=lim) r=mid;
		else l=mid;
	}
	return m*r+p;
}
int main()     
{
	long long m1,m2,r1,r2,d,c,t;
	long long L,R;
	cin>>m1>>r1>>m2>>r2>>L>>R;
	long long kp=Max(r1,r2);
	L=Max(L,kp);
	if(L>R)
	{
		printf("0");
		return 0;  
	}
	r1=(r1%m1+m1)%m1;
	r2=(r2%m2+m2)%m2;
	d=egcd(m1, m2);       
	c=r2-r1;     
	if (c%d)          
	{           
		printf("0");
		return 0;   
	}
	t=m2/d;        
	x=(c/d*x%t+t)%t;       
	r1=m1*x+r1;        
	m1=m1*m2/d;  
	r1=rep(r1,m1,kp);
	long long ans=check(R,m1,r1)-check(L-1,m1,r1);
	cout<<ans;
	return 0;
}    

