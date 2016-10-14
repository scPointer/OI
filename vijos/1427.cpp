#include <cstdio>
#include <cstring>
#define MAXN 10001
#define MAXSTR 260
struct point{
	int len;
	int numofsons;
	int dad;
}po[MAXN];
int n,s,t;
bool vis[MAXN];
void count(int s,int t,int f)
{
	int lens=0,times=0; 
	int p=s;
	while(p!=f)
	{
		times+=po[p].numofsons;
		lens+=po[p].len;
		p=po[p].dad;
	}
	p=t;
	while(p!=f)
	{
		times+=po[p].numofsons;
		lens+=po[p].len;
		p=po[p].dad;
	}
	if(f!=s&&f!=t)times+=po[f].numofsons;
	if(f!=s) times-=po[s].numofsons;
	if(f!=t) times-=po[t].numofsons;
	
	lens+=po[f].len;
	printf("%d\n%d\n",lens,times);
}
int findnearest(int s,int t)
{
	int p=s;
	while(po[p].dad!=0)
	{
		vis[p]=1;
		p=po[p].dad;
	}
	vis[p]=1;
	p=t;
	while(vis[p]==0)
		p=po[p].dad;
	return p;
}
int main()
{
	scanf("%d%d%d",&n,&s,&t);
	for(int i=1;i<=n;i++)
	{
		int p,pdad;
		char pstr[MAXSTR];
		scanf("%d %d %s",&p,&pdad,pstr);
		po[p].len=strlen(pstr);
		po[p].dad=pdad;
		po[pdad].numofsons++;
	}
	int f=findnearest(s,t);
	count(s,t,f);
	return 0;
}
