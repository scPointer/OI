#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
long long R,ans;
long long gcd(long long x,long long y){return x%y==0? y:gcd(y,x%y);}
//int tdd[1050000];
bool check(long long y,double x)
{
      if(x==floor(x))
      {
            long long x1=(long long)floor(x);
            if(gcd(x1*x1,y*y)==1&&x1*x1!=y*y)
                  return true;
      }
      return false;
}
int main()
{
      scanf("%lld",&R);
//	freopen("1041.ans","w",stdout);
//	for(R=1900000000;R<=1900000100;R++)
	{
//		printf("%lld\n",R);
		ans=0;
      for(long long d=1;d<=sqrt(2*R);d++)
      {
            if((2*R)%d==0)
            {
                  for(long long a=1;a<=(long long)sqrt(2*R/(2*d));a++)
                  {
                        double b=sqrt(((2*R)/d)-a*a);
                        if(check(a,b))ans++;
                  }
                  if(d!=(2*R)/d)
                  {
                        for(long long a=1;a<=(long long)sqrt(d/2);a++)
                        {
                              double b=sqrt(d-a*a);
                              if(check(a,b))
                                    ans++;
                        }
                  }
            }
      }    
      printf("%lld\n",ans*4+4); 
//		printf("%lld: %lld\n",R,ans);
//		if(tdd[ans]==0) tdd[ans]=R,printf("%d: %d\n",R,ans);
	  }
      return 0;
}