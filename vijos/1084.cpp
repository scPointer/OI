#include <cstdio>
using namespace std;
#define MAXN 2000
#define BIT 100
#define MMAX(a,b) (a>b?a:b)
int nb[MAXN];
int n;
char line[MAXN+5];
class bigint
{
	public:
		bigint(int k=0)
		{
			reset();
			bi[0]=k;
		}
		void reset()
		{
			top=0;
			for(int i=0;i<=BIT;i++)
				bi[i]=0;
		}
		void print()
		{
			printf("%d",bi[top]);
			for(int i=top-1;i>=0;i--)
				printf("%04d",bi[i]);
			printf("\n");
		}
		void operator =(int k)
		{
			bi[0]=k;
//			arrange();
		}
		void operator =(bigint k)
		{
			for(int i=0;i<=k.top;i++)
				bi[i]=k.bi[i];
			top=k.top;
		}
		bigint operator +(bigint k)
		{
			bigint c;
			c.top=MMAX(k.top,top);
			for(int i=0;i<=c.top;i++)
				c.bi[i]=k.bi[i]+bi[i];
			c.arrange();
			return c;
		}
		void operator *=(int k)
		{
			for(int i=0;i<=top;i++)
				bi[i]*=k;
			arrange();
		}
	protected:
		int top;
		int bi[BIT+1];
	private:
		void arrange()
		{
			int i;
			for(i=0;i<=top||bi[i]!=0;i++)
				if(bi[i]>=10000)
				{
					bi[i+1]+=bi[i]/10000;
					bi[i]%=10000;
				}
			top=i-1;
		}
};
bigint js(1),ans(0);
int main()
{
	scanf("%d",&n);
	while(n!=0)
	{
		scanf("%s",line);
		for(int i=0;i<=n-1;i++)
			if(line[i]>='A'&&line[i]<='C')	nb[i]=line[i]-'A';
			else if(line[i]>='a'&&line[i]<='c') nb[i]=line[i]-'a';
//		bigint js(1),ans(0);
		js.reset();js=1;
		ans.reset();
		for(int i=n-1;i>=0;i--)
		{
			if(nb[i]==1)
				ans=ans+js;
			else if(nb[i]==2)
				ans=ans+js+js;
			js*=3;
		}
		ans.print();
		scanf("%d",&n);
	}
	return 0;
}
