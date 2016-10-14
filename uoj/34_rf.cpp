

//#include<bits/stdc++.h>
#include <cstdio>
#include <complex>
#include <iostream>
#define pi acos(-1)
using namespace std;
typedef complex<double> E;
int n,m;
E a[262145],b[262145];
void fft(E *x,int n,int type)
{
    if(n==1)return;
		
	printf("n=%d\n",n);
	for(int i=0;i<n;i++)
		cout<<x[i]<<endl;
	
	E l[n>>1],r[n>>1];
	for(int i=0;i<n;i+=2)
		l[i>>1]=x[i],r[i>>1]=x[i+1];
	
	printf("l=%d\n",(n>>1)-1);
	for(int i=0;i<n/2;i++)
		cout<<l[i]<<endl;
	printf("r=%d\n",(n>>1)-1);
	for(int i=0;i<n/2;i++)
		cout<<r[i]<<endl;
	
	fft(l,n>>1,type);fft(r,n>>1,type);
	
	printf("AFTER\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("l=%d\n",(n>>1)-1);
	for(int i=0;i<n/2;i++)
		cout<<l[i]<<endl;
	printf("r=%d\n",(n>>1)-1);
	for(int i=0;i<n/2;i++)
		cout<<r[i]<<endl;
	
	E wn(cos(2*pi/n),sin(type*2*pi/n)),w(1,0),t;
	for(int i=0;i<n>>1;i++,w*=wn)
		t=w*r[i],x[i]=l[i]+t,x[i+(n>>1)]=l[i]-t;
	
	printf("RUN n=%d\n",n);
	for(int i=0;i<=n;i++)
		cout<<x[i]<<endl;
	
}
int main()
{
	freopen("p78test.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0,x;i<=n;i++)scanf("%d",&x),a[i]=x;
	for(int i=0,x;i<=m;i++)scanf("%d",&x),b[i]=x;
	
	m=n+m;for(n=1;n<=m;n<<=1);
	fft(a,n,1);
	printf("cut\n\n\n\n\n");
	fft(b,n,1);
	for(int i=0;i<=n;i++)a[i]=a[i]*b[i];
	
	for(int i=0;i<=n;i++)cout<<a[i]<<endl;
	
	fft(a,n,-1);
	for(int i=0;i<=m;i++)
		printf("%d ",(int)(a[i].real()/n+0.5));
	return 0;
}

