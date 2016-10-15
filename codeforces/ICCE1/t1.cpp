#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
typedef priority_queue<int> pqi;
#define NDS 3300000
#define N 100005
#define lowbit(x) (x&(-x))
pqi* null;
int ls[NDS],rs[NDS],cnt[NDS],ndcnt;
bool has[NDS];
int add(int p,int v,int bs)
{
	int np=++ndcnt;cnt[np]=cnt[p]+1;has[np]=has[p];
	if(bs==-1){has[np]=1;ls[np]=ls[p];rs[np]=rs[p];return np;}
	if((v>>bs)&1)
	{
		ls[np]=ls[p];
		rs[np]=add(rs[p],v,bs-1);
	}
	else
	{
		ls[np]=add(ls[p],v,bs-1);
		rs[np]=rs[p];
	}
	return np;
}
pqi* dfs(int p,int v)
{
	pqi* res=null;
	if(ls[p]!=0 && rs[p]!=0)
	{
		pqi* lv=dfs(ls[p],v<<1);
		pqi* rv=dfs(rs[p],(v<<1)+1);
		if(lv->size() < rv->size()) swap(lv,rv);
		while(!rv->empty())
		{
			lv->push(rv->top());
			rv->pop();
		}
		res=lv;
	}
	else if(ls[p]!=0)
		res=dfs(ls[p],v<<1);
	else if(rs[p]!=0)
		res=dfs(rs[p],(v<<1)+1);
	if(has[p])
	{
		if(res==null) res=new pqi();
		res->push(v);
	}
	else if(v>0)
	{
		res->pop();
		res->push(v);
	}
	return res;
}
int rd[N];
int main()
{
	null=new pqi();
	int n;scanf("%d",&n);
	int rot=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&rd[i]);
	sort(rd+1,rd+1+n);
	for(int i=1;i<=n;i++)
	{
		int p=rd[i];
		int ds=0;
		for(int j=p;j;j>>=1)
			ds++;
		rot=add(rot,p,ds-1);
	}
	pqi *ans=dfs(rot,0);
	while(!ans->empty())
	{
		printf("%d ",ans->top());
		ans->pop();
	}
}
