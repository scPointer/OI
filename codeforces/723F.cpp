#include <cstdio>
#define N 800005
#define M 800005
int efr[M<<1],eg[M<<1],nxt[M<<1],head[N],egtot;
int tips[N],tipt[N];
bool tip[M<<1];
int n,m,S,T;
void addEdge(int p1,int p2)
{
	efr[egtot]=p1;
	eg[egtot]=p2;
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}

int dset[N],cnt;
int dfind(int p){return dset[p]==p? p:dset[p]=dfind(dset[p]);}
void merge(int p1,int p2,int id)
{
	int f1=dfind(p1);
	int f2=dfind(p2);
	if(f1!=f2)
	{
		tip[id]=tip[id^1]=1;
		dset[f1]=f2,cnt--;
	}
}

bool viss[N],vist[N];
int pra[N],prb[N],pcnt;
void add(int p1,int p2){++pcnt;pra[pcnt]=p1;prb[pcnt]=p2;}
bool tryToLinkST(int linked,int ds,int dt)
{
	pcnt=0;
	if(linked && ds>0 && dt>0)
	{
		--ds,--dt;
		add(S,T);
	}
	else return 0;
	for(int i=1;i<=n;i++)
	{
		if(viss[i] && !vist[i])
			add(S,tips[i]);
		else if(vist[i] && !viss[i])
			add(T,tipt[i]);
		else if(viss[i] && vist[i])
		{
			if(ds>0)
				add(S,tips[i]),ds--;
			else if(dt>0)
				add(T,tipt[i]),dt--;
			else return 0;
		}
	}
	for(int i=0;i<=egtot;i+=2)
		if(tip[i])
			add(efr[i],eg[i]);
	return 1;
}
bool tryNotToLinkST(int ds,int dt)
{
	pcnt=0;
	int togt=1;
	for(int i=1;i<=n;i++)
	{
		if(viss[i] && !vist[i])
			add(S,tips[i]);
		else if(vist[i] && !viss[i])
			add(T,tipt[i]);
		else if(viss[i] && vist[i])
		{
		
			if(togt)
			{
				if(ds==0 || dt==0) return 0;
				add(S,tips[i]),ds--;
				add(T,tipt[i]),dt--;
				togt=0;
				continue;
			}
			
			if(ds>0)
				add(S,tips[i]),ds--;
			else if(dt>0)
				add(T,tipt[i]),dt--;
		}
	}
	for(int i=0;i<=egtot;i+=2)
		if(tip[i])
			add(efr[i],eg[i]);
	return togt==0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		head[i]=-1;
	for(int i=1;i<=n;i++)
		dset[i]=i;
	cnt=n-2;
	for(int i=1;i<=m;i++)
	{
		int p1,p2;scanf("%d%d",&p1,&p2);
		addEdge(p1,p2);
		addEdge(p2,p1);
	}
	int ds,dt;
	int ls=0,lt=0,lst=0,nl=0;
	int STLinked=0;
	scanf("%d%d%d%d",&S,&T,&ds,&dt);
	for(int j=head[S];~j;j=nxt[j])
		if(eg[j]==T)
			STLinked=1;
	for(int i=1;i<=n;i++)
	{
		if(i==S || i==T) continue;
		for(int j=head[i];~j;j=nxt[j])
		{
			if(eg[j]==S || eg[j]==T) continue;
			merge(i,eg[j],j);
		}
	}
	nl=cnt;
	for(int j=head[S];~j;j=nxt[j])
	{
		int pt=dfind(eg[j]);
		if(pt==T) continue;
		if(!viss[pt])
		{
			viss[pt]=1,--nl,++ls;
			tips[pt]=eg[j];
		}
	}
	for(int j=head[T];~j;j=nxt[j])
	{
		int pt=dfind(eg[j]);
		if(pt==S) continue;
		if(!vist[pt])
		{
			vist[pt]=1;
			if(viss[pt]) --ls,++lst;
			else --nl,++lt;
			tipt[pt]=eg[j];
		}
	}
	ds-=ls;
	dt-=lt;
	if(nl>0 || ds<0 || dt<0 || ds+dt<lst+1)
	{
		puts("No");
		return 0;
	}
	
	if(!tryToLinkST(STLinked,ds,dt))
		if(!tryNotToLinkST(ds,dt))
		{
			puts("No");
			return 0;
		}
	puts("Yes");
	for(int i=1;i<=pcnt;i++)
		printf("%d %d\n",pra[i],prb[i]);
}
