#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
typedef long long ll;

map<int,int> mp;
map<int,int>::iterator it;
int fpw(int a,int b,int mo)
{
	int res=1;
	while(b)
	{
		if(b&1) res=(ll)res*a%mo;
		a=(ll)a*a%mo;
		b>>=1;
	}
	return res;
}
int gcd(int a,int b)
{
	if(a<b) return gcd(b,a);
	else if(b==0) return a;
	else return gcd(b,a%b);
}
int getphi(int p)
{
	int res=p;
	int sr=(int)sqrt(p)+1;
	for(int i=2;i<=sr;i++)
		if(p%i==0)
		{
			res=(ll)res*(i-1)/i;
			while(p%i==0)
				p/=i;
		}
	if(p>1) res=(ll)res*(p-1)/p;
	return res;
}
int main()
{
//	freopen("2242.in","r",stdin);
	int T,type;scanf("%d%d",&T,&type);
	if(type==1)
	{
		while(T--)
		{
			int a,b,p;scanf("%d%d%d",&a,&b,&p);
			a%=p;b%=p;
			printf("%d\n",fpw(a,b,p));
		}
	}
	else if(type==2)
	{
		while(T--)
		{
			int a,b,p;scanf("%d%d%d",&a,&b,&p);
			a%=p;
			int g=gcd(a,p);
			if(b%g || (a==0 && b>0)){printf("Orz, I cannot find x!\n");continue;}
			else if(a==0 && b==0){printf("0\n");continue;}
			a/=g;b/=g;p/=g;
			int phi=getphi(p);
			int ans=(ll)b*fpw(a,phi-1,p)%p;
			printf("%d\n",ans);
		}
	}
	else
	{
		while(T--)
		{
			int a,b,p;scanf("%d%d%d",&a,&b,&p);
			a%=p;
			int phi=getphi(p);
			if(a==0 && b==0){printf("1\n");continue;}
			else if(a==0 || gcd(a,p)>1) {printf("Orz, I cannot find x!\n");continue;}
				int sq=(int)sqrt(p);
				int res=1,ans=-1;
				for(int i=0;i<sq;i++)
				{
					it=mp.find(res);
					if(it==mp.end())
						mp[res]=i;
					res=(ll)res*a%p;
				}
				for(int i=0;i<=p;i+=sq)
				{
					res=(ll)b*fpw(fpw(a,i,p),phi-1,p)%p;
					it=mp.find(res);
					if(it!=mp.end())
					{
						ans=i+it->second;
						break;
					}
				}
				if(ans>-1) printf("%d\n",ans);
				else printf("Orz, I cannot find x!\n");
		}
	}
}
