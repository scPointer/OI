#include <cstdio>
#include <iostream>
#define N 1005
#define MO 998244353
#define dMax(a,b) (a<b?(a)=(b):0)
inline int RD()
{
	static int res,sgn;
	static char cr;
	while( ((cr=getchar())<'0' || cr>'9') && cr!='-');
	cr=='-'? (sgn=-1,res=0) : (sgn=1,res=cr-'0');
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res*sgn;
}
long long que[N][2],qtail;
int tp,m;
inline long long cross(long long x1,long long y1,long long x2,long long y2){return x1*y2-x2*y1;}
void solve1()
{
	long long maxu,ans=0;
	for(long long t,l,r,x,y;m>0;m--)
	{
		t=RD();
		if(t==2) qtail--;
		else if(t==1)
		{
			que[++qtail][0]=RD();
			que[qtail][1]=RD();
		}
		else
		{
			l=RD();r=RD();x=RD();y=RD();
			maxu=cross(x,y,que[l][0],que[l][1]);
			for(int i=l+1;i<=r;i++)
				dMax(maxu,cross(x,y,que[i][0],que[i][1]));
//			printf("%d]%lld\n",m,maxu);
			maxu=(maxu%MO+MO)%MO;
			ans^=maxu;
		}
	}
	std::cout<<ans<<std::endl;
}
int main()
{
//	freopen("ex_unknown2.in","r",stdin);
	tp=RD();
	while((m=RD())>0)
	{
		qtail=0;
//		if(tp==1)
			solve1();
	}
	return 0;
}
