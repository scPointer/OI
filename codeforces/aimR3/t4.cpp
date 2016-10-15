#include <cstdio>
#include <iostream>
#define impsb {printf("Impossible");return 0;}
long long check(long long p)
{
	long long l=0,r=100000,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(mid*(mid-1)/2<=p) l=mid;
		else r=mid;
	}
	if(l<=1) return -2;
	else if(l*(l-1)/2==p) return l;
	else return -1;
}
int main()
{
	long long a00,a01,a10,a11;
	std::cin>>a00>>a01>>a10>>a11;
	if(a00+a01+a10+a11==0) {printf("1");return 0;}
	long long len0=check(a00);
	long long len1=check(a11);
	long long sum=check(a00+a01+a10+a11);
	if(len0==-1 || len1==-1 || sum==-1) impsb;
	if(len0==-2 && len1==-2)
	{
		if(a01==1 && a10==0) {printf("01");return 0;}
		else if(a10==1 && a01==0) {printf("10");return 0;}
		else impsb;
	}
	else if(len0==-2) len0=sum-len1;
	else if(len1==-2) len1=sum-len0;
	long long q=len0*len1;
	if(a01>q || a10>q || a01+a10!=q) impsb;
	if(len0==0)
	{
		while(sum--)
			putc('1',stdout);
		return 0;
	}
	else if(len1==0)
	{
		while(sum--)
			putc('0',stdout);
		return 0;
	}
	long long r1=a01/len1;
	long long r2=a01%len1;
	for(int i=1;i<=r1;i++)
		putc('0',stdout);
	for(int i=1;i<=len1-r2;i++)
		putc('1',stdout);
	if(len0>r1)
		putc('0',stdout);
	for(int i=1;i<=r2;i++)
		putc('1',stdout);
	for(int i=1;i<=len0-r1-1;i++)
		putc('0',stdout);
}
