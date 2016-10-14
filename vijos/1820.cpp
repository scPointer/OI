#include <cstdio>
#define MAXN 10005
struct Edge{int pfr,pto,id,next;};
Edge ed[MAXN*2];
int head[MAXN],edtop;

int stack[MAXN],place[MAXN],sttop,pre[MAXN];
int vistime[MAXN],nowtime;
bool ifgot[MAXN],gote[MAXN*2];
int ans[MAXN],rans[MAXN];
int n;
void addedge(int p1,int p2,int id)
{
	ed[edtop++]=(Edge){p1,p2,id,head[p1]};
	head[p1]=edtop-1;
}
void havefound(int l,int r,int lastedge)
{
	int minp=n+1;
	for(int i=l;i<=r;i++)
		if(ed[pre[stack[i]]].id<ed[minp].id)
			minp=pre[stack[i]];
	if(ed[minp].pfr>ed[minp].pto)
	{
//		ans[ed[lastedge].id]=stack[r];
		ans[stack[r]]=ed[lastedge].id;
//		ifgot[ed[lastedge].id]=1;
		ifgot[stack[r]]=1;
		gote[lastedge]=1;
		for(int i=l+1;i<=r;i++)
		{
//			ans[ed[pre[stack[i]]].id]=stack[i-1];
			ans[stack[i-1]]=ed[pre[stack[i]]].id;
//			ifgot[ed[pre[stack[i]]].id]=1;
			ifgot[stack[i-1]]=1;
			gote[pre[stack[i]]]=gote[pre[stack[i]]^1]=1;
		}
	}
	else
	{
//		ans[ed[lastedge].id]=stack[l];
		ans[stack[l]]=ed[lastedge].id;
//		ifgot[ed[lastedge].id]=1;
		ifgot[stack[l]]=1;
		gote[lastedge]=1;
		for(int i=l+1;i<=r;i++)
		{
//			ans[ed[pre[stack[i]]].id]=stack[i];
			ans[stack[i]]=ed[pre[stack[i]]].id;
//			ifgot[ed[pre[stack[i]]].id]=1;
			ifgot[stack[i]]=1;
			gote[pre[stack[i]]]=gote[pre[stack[i]]^1]=1;
		}
	}
}
bool DFS(int p)
{
	stack[++sttop]=p;
	place[p]=sttop;
	for(int i=head[p];i>=0;i=ed[i].next)
	{
		if(gote[i]==1 ||(pre[p]!=0 && pre[p]==(i^1))) continue;
		if(place[ed[i].pto]!=0&&place[p]-place[ed[i].pto]>=2)
		{
			havefound(place[ed[i].pto],place[p],i);
		}
		if(ifgot[ed[i].pto]==1&&gote[i]==0)
		{
			if(ifgot[p]==0)
			{
				ifgot[p]=1;
				gote[i]=gote[i^1]=1;
				ans[p]=ed[i].id;
			}
			else return 0;
		}
		pre[ed[i].pto]=i;
		if(DFS(ed[i].pto)==0) return 0;
	}
	if(ifgot[p]==0)
	{
		if(pre[p]==0) return 0;
		else
		{
			ifgot[p]=1;
			gote[pre[p]]=gote[pre[p]^1]=1;
			ans[p]=ed[pre[p]].id;
		}
	}
	stack[sttop--]=0;
	place[p]=0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) head[i]=-1;
	for(int i=1;i<=n;i++)
	{
		int di;
		scanf("%d",&di);
		int p1=((i-di-1)+n)%n+1;
		int p2=((i+di-1)+n)%n+1;
		if(p1==p2)
		{
			ans[i]=p1;
			ifgot[i]=1;
		}
		else
		{
			addedge(p1,p2,i);
			addedge(p2,p1,i);
		}
	}
	nowtime=1;
	for(int i=1;i<=n;i++)
		if(ifgot[i]==0)
		{
			if(DFS(i)==0){printf("No Answer");return 0;}
		}
	for(int i=1;i<=n;i++)
		rans[ans[i]]=i-1;
	for(int i=1;i<=n;i++)
		printf("%d ",rans[i]);
	return 0;
}
