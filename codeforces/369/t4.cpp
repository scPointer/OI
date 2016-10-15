#include <cstdio>
#include <iostream>
#define N 200005
#define mo 1000000007
typedef long long ll;
int eg[N*2],nxt[N*2],head[N],egtot;
int used[N*2];
void addEdge(int p1,int p2)
{
	eg[egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}
int h[N],cnt[N],rd[N];
int tim[N],timetip;
void dfs(int p)
{
	cnt[p]=1;tim[p]=timetip;
	for(int i=head[p];~i;i=nxt[i])
		if(!used[i>>1])
		{
			used[i>>1]=1;
			if(h[eg[i]]!=0)
			{
				rd[p]=h[p]-h[eg[i]]+1;
				continue;
			}
			h[eg[i]]=h[p]+1;
			dfs(eg[i]);
			cnt[p]+=cnt[eg[i]];
			if(rd[eg[i]]) rd[p]=rd[eg[i]];
		}
}
int pto[N];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		head[i]=-1;
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		addEdge(i,p);
		addEdge(p,i);
		pto[i]=p;
	}
	ll ans=1;
	for(int i=1;i<=n;i++)
	{
		if(h[i]==0)
		{
			++timetip;
			h[i]=1;
			dfs(i);
			ll res1=1,res2=1;
			for(int j=1;j<=cnt[i];j++)
				res1=res1*2%mo;
			for(int j=1;j<=cnt[i]-rd[i]+1;j++)
				res2=res2*2%mo;
			res1=(res1-res2+mo)%mo;
			ans=ans*res1%mo;
		}
	}
	std::cout<<ans;
}