#include <cstdio>
#define MAXN 3000005
#define MAXBIT 100
#define INW 100000000
#define max(a,b) (a>b?a:b)
struct bigint
{
	bigint(int k=0){top=0;bi[0]=k;}
	void set(int k=0){top=0;bi[0]=k;}
	void print()
	{
		printf("%d",bi[top]);
		for(int i=top-1;i>=0;i--)
			printf("%08d",bi[i]);
		printf("\n");
	}
	int gettop(){return top;}
	friend void addup(bigint& a,bigint& b,bigint& c);
	int bi[MAXBIT/8+1];
	int top;
}f[MAXN/2];
void addup(bigint& a,bigint& b,bigint& c)
{
	int i;
	a.top=max(c.top,b.top);
	for(i=0;i<=a.top;i++)
		a.bi[i]=b.bi[i]+c.bi[i];
	for(i=0;i<=a.top||a.bi[i]!=0;i++)
		if(a.bi[i]>=INW)
		{
			a.bi[i+1]+=a.bi[i]/INW;
			a.bi[i]%=INW;
		}
	a.top=i-1;
}
int maxn;
int main()
{
	f[0].set(1);
	maxn=0;
	int n;
	while(scanf("%d",&n)==1)
	{
		n/=2;
		if(maxn>=n)
			f[n].print();
		else
		{
			while(++maxn<=n)
				addup(f[maxn],f[maxn/2],f[maxn-1]);
			f[--maxn].print();
		}
	}
	return 0;
}
