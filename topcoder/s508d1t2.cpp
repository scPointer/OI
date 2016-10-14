#include <cstdio>
#include <cstring>
#include <vector>
#define mo 1000000009
#define BIT 59
using namespace std;
long long lim[12];
long long bts[64];
long long f[62][1<<11];
int n;
class YetAnotherORProblem{
	public:
	long long dfs(int bt,int tip)
	{
		if(bt==-1) return 1;
		if(f[bt][tip]!=-1) return f[bt][tip];
		long long res=0;
		for(int i=0;i<n;i++)
			if((tip&(1ll<<i))==0 || (lim[i]&(1ll<<bt)))
				res=(res+dfs(bt-1,(tip&bts[bt]) | (tip&(1ll<<i))))%mo;
		res=(res+dfs(bt-1,tip&bts[bt]))%mo;
		if(f[bt][tip]==-1) f[bt][tip]=res; 
		return res;
	}
	int countSequences(vector<long long> R){
		n=R.size();
		for(int i=0;i<n;i++) lim[i]=R[i];
		for(int i=BIT;i>=0;i--)
		{
			bts[i]=(1<<n)-1;
			for(int j=0;j<n;j++)
				if(lim[j]&(1ll<<i))
					bts[i]^=1<<j;
		}
		memset(f,-1,sizeof(f));
		long long ans=dfs(BIT,(1ll<<n)-1);
		return (int)ans;
	}
};
YetAnotherORProblem obj;
vector<long long> vc;
int main()
{
	long long a;
	while(~scanf("%lld",&a))
		vc.push_back(a);
	printf("%d",obj.countSequences(vc));
}