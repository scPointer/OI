#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
#define MAXN 105
vector<int> g[MAXN];
stack<int> st;
int vist[MAXN],mlink[MAXN],scc[MAXN];
int nowtime,sccnum;

bool id[MAXN],od[MAXN];//if in/out degree equal to zero
int n;
void dfs(int p)
{
    vist[p]=mlink[p]=++nowtime;
    st.push(p);
    for(int i=0;i<g[p].size();i++)
    {
        int q=g[p][i];
        if(vist[q]==0)
        {
            dfs(q);
            mlink[p]=min(mlink[p],mlink[q]);
        }
        else if(scc[q]==0)
            mlink[p]=min(mlink[p],mlink[q]);
    }
	if(vist[p]==mlink[p])
	{
		sccnum++;
		int r;
		do
		{
			r=st.top();
			st.pop();
			scc[r]=sccnum;
		}while(r!=p);
	}
}
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int r;
        scanf("%d",&r);
        while(r!=0)
        {
            g[i].push_back(r);
            scanf("%d",&r);
        }
    }
    for(int i=1;i<=n;i++)
        if(vist[i]==0)
			dfs(i);
	for(int i=1;i<=n;i++)
		for(int j=0;j<g[i].size();j++)
            if(scc[i]!=scc[g[i][j]])
				od[scc[i]]=id[scc[g[i][j]]]=1;
	int ind0=0,outd0=0;
    for(int i=1;i<=sccnum;i++)
    {
        if(od[i]==0) outd0++;
        if(id[i]==0) ind0++;
    }
	if(sccnum>1) printf("%d\n%d",ind0,max(ind0,outd0));
	else printf("1\n0");
	return 0;
}
