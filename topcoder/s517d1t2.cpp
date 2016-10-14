#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define mo 1000000007
int f[55][55],n;
bool dir[55];
bool vis[55];
int cnt;
class AdjacentSwaps{
	public:
	int theCount(vector <int> p){
		n=p.size();
		for(int i=0,j;i<n;i++){
			for(j=i;p[j]!=i;j++);
			for(;j>i;j--){
				cnt++;
				if(vis[j]==1) return 0;
				vis[j]=1;
				if(vis[j-1]) dir[j]=1;
				swap(p[j],p[j-1]);
			}
		}
		if(cnt!=n-1) return 0;
		f[1][1]=1;
		for(int i=2;i<=n-1;i++)
			if(dir[i]){
				for(int j=1;j<=i;j++)
					f[i][j]=(f[i][j-1]+f[i-1][j-1])%mo;
			}
			else{
				for(int j=i;j>=1;j--)
					f[i][j]=(f[i][j+1]+f[i-1][j])%mo;
			}
		int ans=0;
		for(int i=1;i<=n-1;i++) ans=(ans+f[n-1][i])%mo;
		return ans;
	}
};
AdjacentSwaps obj;
int main()
{
	vector<int> vc;
	int n; scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		vc.push_back(p);
	}
	printf("%d",obj.theCount(vc));
}