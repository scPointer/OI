#include <cstdio>
#define N 1000005
#define L 1005
inline int RD()
{
	char cr;
	int res;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
struct Query{int tp,v1,v2,used;}qe[N];
int fa[N];
int fson[N],bro[N];
int dset[N];
int ans[N];
int DFind(int p){return dset[p]==p? p:dset[p]=DFind(dset[p]);}
int chg[L],cnt[L],has[L][L];
int n,m;
void addSon(int p,int s)
{
	fa[s]=p;
	bro[s]=fson[p];
	fson[p]=s;
}
void dfs(int p)
{
	if(p==0)
	{
		for(int i=fson[p];i;i=bro[i])
			dfs(i);
		return;
	}
	int qx=qe[p].v1,qy=qe[p].v2;
	if(qe[p].tp==1)
	{
		if((chg[qx]^has[qx][qy])==0)
		{
			ans[p]=ans[fa[p]]+1;
			qe[p].used=1;
			has[qx][qy]^=1;
			cnt[qx]++;
		}
		else
		{
			ans[p]=ans[fa[p]];
			qe[p].used=0;
		}
	}
	else if(qe[p].tp==2)
	{
		if((chg[qx]^has[qx][qy])==1)
		{
			ans[p]=ans[fa[p]]-1;
			qe[p].used=1;
			has[qx][qy]^=1;
			cnt[qx]--;
		}
		else
		{
			ans[p]=ans[fa[p]];
			qe[p].used=0;
		}
	}
	else if(qe[p].tp==3)
	{
		chg[qx]^=1;
		ans[p]=ans[fa[p]]+m-cnt[qx]-cnt[qx];
		cnt[qx]=m-cnt[qx];
		qe[p].used=1;
	}
	for(int i=fson[p];i;i=bro[i])
		dfs(i);
	if(qe[p].used)
	{
		if(qe[p].tp==1)
		{
			cnt[qx]--;
			has[qx][qy]^=1;
		}
		else if(qe[p].tp==2)
		{
			cnt[qx]++;
			has[qx][qy]^=1;
		}
		else
		{
			chg[qx]^=1;
			cnt[qx]=m-cnt[qx];
		}
	}
}
int main()
{
	int q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=q;i++)
		dset[i]=i;
	int now=0;	
	for(int i=1;i<=q;i++)
	{
		qe[i].tp=RD();
		qe[i].v1=RD();
		if(qe[i].tp<=2) qe[i].v2=RD();
		if(qe[i].tp==4) now=dset[i]=dset[qe[i].v1];
		else addSon(dset[i-1],i),now=i;
	}
	dfs(0);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[dset[i]]);
}
