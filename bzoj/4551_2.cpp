#include <cstdio>
#define N 100050
int eg[N*2],nxt[N*2],head[N],egtot;
int fa[N];
bool tp[N];
int gp[N];
int dset[N];
int cnt[N];
int ans[N];
int timetip;
void addEdge(int p1,int p2)
{
	eg[++egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot;
}
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
void setTree(int p)
{
	dset[p]= cnt[p]? p: fa[p];
	for(int i=head[p];i;i=nxt[i])
		if(eg[i]!=fa[p])
			{
				fa[eg[i]]=p;
				setTree(eg[i]);
			}
}
int main()
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	char s[3];
	cnt[1]++;
	for(int i=1;i<=Q;i++)
	{
		scanf("%s%d",s,&gp[i]);
		tp[i]= s[0]=='Q'? 0:1;
		if(tp[i]) cnt[gp[i]]++;
	}
	setTree(1);
	int anscnt=0;
	for(int i=Q;i>=1;i--)
	{
		if(tp[i]==1)
		{
			cnt[gp[i]]--;
			if(cnt[gp[i]]==0) dset[gp[i]]=fa[gp[i]];
		}
		else
			ans[++anscnt]=find(gp[i]);
	}
	while(anscnt)
		printf("%d\n",ans[anscnt--]);
}
