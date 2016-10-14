#include <cstdio>
#define NN 1000005
#define Min(a,b) (a<b?a:b)
int inv[NN];
class DivideAndShift{
	public:
	int getLeast(int n, int m){
		int ans=2000000;
		for(int i=1;i<=n;i++)
			if(n%i==0)
			{
				for(int j=2;j<=i;j++)
					if(i%j==0){
						inv[i]=inv[i/j]+1;
						break;
					}
				int pos=(m-1)%(n/i)+1;
				int res=inv[i]+Min(pos-1,n/i-pos+1);
				ans=Min(ans,res);
			}
		return ans;
	}
};
DivideAndShift obj;
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	printf("%d",obj.getLeast(n,m));
}