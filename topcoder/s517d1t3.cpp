#include <cstdio>
#include <string>
#include <vector>
using namespace std;
#define Min(a,b) (a<b?a:b)
int ans,n,m;
int painted;
int mp[55][55];
int stk[105][55];
int ccnt;
bool vis1[55],vis2[55];
class ColorfulBoard{
	public:
	inline int check1(int p)
	{
		int col=0;
		for(int i=1;i<=m;i++)
			if(mp[p][i]){
				if(col==0) col=mp[p][i];
				else if(mp[p][i]!=col) return -1;
			}
		return col;
	}
	inline int check2(int p)
	{
		int col=0;
		for(int i=1;i<=n;i++)
			if(mp[i][p]){
				if(col==0) col=mp[i][p];
				else if(mp[i][p]!=col) return -1;
			}
		return col;
	}
	inline void cover1(int p,int stg){for(int i=1;i<=m;i++){stk[stg][i]=mp[p][i];mp[p][i]=0;}}
	inline void cover2(int p,int stg){for(int i=1;i<=n;i++){stk[stg][i]=mp[i][p];mp[i][p]=0;}}
	inline void recover1(int p,int stg){for(int i=1;i<=m;i++) mp[p][i]=stk[stg][i];}
	inline void recover2(int p,int stg){for(int i=1;i<=n;i++) mp[i][p]=stk[stg][i];}
	void dfs(int stg)
	{
		if(stg>=ans || ++ccnt>=2000000) return;
		int if0=0,ifn=0,ifa=0;
		for(int i=1,cc;i<=n;i++)
			if(vis1[i]==0){
				cc=check1(i);
				if(cc<=0){
					cc==0? if0++: ifn++;
					continue;
				}
				ifa++;
				cover1(i,stg);
				vis1[i]=1;
				dfs(stg+1);
				vis1[i]=0;
				recover1(i,stg);
			}
		for(int i=1,cc;i<=m;i++)
			if(vis2[i]==0){
				cc=check2(i);
				if(cc<=0){
					cc==0? if0++: ifn++;
					continue;
				}
				ifa++;
				cover2(i,stg);
				vis2[i]=1;
				dfs(stg+1);
				vis2[i]=0;
				recover2(i,stg);
			}
		if(ifa==0 && if0)
			ans=Min(ans,stg);
//		printf("stg%d\n",stg);
	}
	int theMin(vector <string> board){
		ans=3000;
		n=board.size();
		m=board[0].length();
		painted=n*m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				mp[i+1][j+1]= board[i][j]>='a'? board[i][j]-'a'+1: board[i][j]-'A'+1+26;
		dfs(0);
		return ans==3000? -1: ans;
	}
};
ColorfulBoard obj;
int main()
{
	char s[100];
	vector<string> x;
	int n; scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		x.push_back(s);
	}
	printf("%d\n",obj.theMin(x));
}