#include <cstdio>
#include <cstring>
#define MAXN 201
struct edge{
	int pto;
	int next;
}ed[MAXN*MAXN];
int head[MAXN],edtop;
int dset[MAXN];
int pla[MAXN];
int stack[MAXN];
bool hassearch[MAXN];
bool leftset[MAXN];

int count;
int find(int p)
{
	if(dset[p]!=p) dset[p]=find(dset[p]);
	return dset[p];
}
void readedge(int p1,int p2)
{
	edtop++;
	ed[edtop].pto=p2;
	ed[edtop].next=head[p1];
	head[p1]=edtop;
}
void dfs(int p,int top)
{
	stack[top]=p;
	pla[p]=top;
	if(hassearch[p]==1) return;
	hassearch[p]=1;
	int k=head[p];
	while(ed[k].pto!=0)
	{
		int np=ed[k].pto;
		if(pla[np]!=0)
			for(int i=top;i>=pla[np]+1&&dset[stack[i]]!=dset[np];i--)
				dset[stack[i]]=dset[np];
		else dfs(np,top+1);
		k=ed[k].next;
	}
	pla[p]=0;
	stack[top]=0;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		dset[i]=i;
	for(int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		while(k!=0)
		{
			readedge(i,k);
			scanf("%d",&k);
		}
	}
	for(int i=1;i<=n;i++)
		if(hassearch[i]==0) dfs(i,1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int belset=find(i);
		if(leftset[belset]==0)
		{
			leftset[belset]=1;
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
