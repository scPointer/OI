#include <cstdio>
#include <iostream>
#define mo 1000000007
#define N 10000005
typedef long long ll;
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
inline int fpower(ll a,ll b)
{
	ll res=1;b%=(mo-1);
	while(b)
	{
		if(b&1) res=res*a%mo;
		a=(a*a)%mo;
		b>>=1;
	}
	return (int)res;
}
int ag[N];
int mn[N];
int a[N];
int sum[N];
bool ismj[N];
void init(int n)
{
	mn[1]=1;
	for(int i=2;i<=n;i++)
		if(mn[i]) continue;
		else 
		{
			mn[i]=i;ag[i]=1;
			if((ll)i*i<=n)
			{
				mn[i]=i;
				for(int j=i*i;j<=n;j+=i)
					if(!mn[j]) mn[j]=i,ag[j]=j/mn[j];
			}
		}

}
int main()
{
//	freopen("t2.in","r",stdin);
	int n,Q;
	long long d;
	std::cin>>n>>d>>Q;
	
//	int c1=clock();
	
	init(n);
//	printf("%d\n",clock()-c1);
	for(int i=1;i<=n;i++)
		if(mn[i]==i) a[i]=fpower(i,d);
		else a[i]=(ll)a[mn[i]]*a[ag[i]]%mo;
//	printf("%d\n",clock()-c1);
	for(int i=2,j;i<=n;i++)
	{
		j=ag[i];
		while(j%mn[i]==0)
			j/=mn[i];
		if(j==1) ismj[i]=1;
		else mn[i]=i/j,ag[i]=j;
	}
//	printf("%d\n",clock()-c1);
	sum[1]=1;
	for(int i=2;i<=n;i++)
		if(ismj[i]) sum[i]=((ll)sum[ag[i]]+a[i])%mo;
		else sum[i]=((ll)sum[mn[i]]*sum[ag[i]])%mo;
	for(int i=1;i<=n;i++)
		sum[i]=(sum[i-1]+sum[i])%mo;
		
//	printf("%d\n",(clock()-c1));
		
	for(int i=1,l,r;i<=Q;i++)
	{
		l=RD();r=RD();
		printf("%d\n",(int)(((ll)sum[r]-sum[l-1]+mo)%mo));
	}
}
