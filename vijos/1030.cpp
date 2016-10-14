#include <cstdio>
#include <algorithm>
using namespace std;
#define N 27
#define M 11
bool discovered[N],used[N];
int apr[N],cnt;
int mp[M][M];
int le[N],ri[N],up[N],dn[N];
int n,m;
char cr;
bool floyd[N][N];
int printout[N],prtop;
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			while((cr=getchar())!='.' &&(cr<'A' ||cr>'Z'));
			x= cr=='.'? -1: cr-'A';
			mp[i][j]=x;
			if(x==-1) continue;
			if(!discovered[x])
			{
				discovered[x]=1;
				le[cr-'A']=ri[cr-'A']=j;
				up[cr-'A']=dn[cr-'A']=i;
			}
			else
			{
				le[x]=min(le[x],j);
				ri[x]=max(ri[x],j);
				up[x]=min(up[x],i);
				dn[x]=max(dn[x],i);
			}
		}
}
void cover_relation()
{
	for(int i=0;i<26;i++)
		if(discovered[i])
		{
			int x=up[i],y=le[i];
			while(++y<ri[i])
				if(mp[x][y]!='0' && mp[x][y]!=i)
					floyd[i][mp[x][y]]=1;
			while(++x<dn[i])
				if(mp[x][y]!='0' && mp[x][y]!=i)
					floyd[i][mp[x][y]]=1;
			while(--y>le[i])
				if(mp[x][y]!='0' && mp[x][y]!=i)
					floyd[i][mp[x][y]]=1;
			while(--x>up[i])
				if(mp[x][y]!='0' && mp[x][y]!=i)
					floyd[i][mp[x][y]]=1;
		}
}
void linkmap()
{
	for(int i=0;i<26;i++) floyd[i][i]=1;
	for(int k=0;k<26;k++)
		for(int i=0;i<26;i++)
			for(int j=0;j<26;j++)
				if(floyd[i][k] && floyd[k][j])
					floyd[i][j]=1;
}
void dfs(int p)
{
	if(p==cnt)
	{
		for(int i=0;i<cnt;i++)
			putchar(printout[i]+'A');
		putchar('\n');
		return;
	}
	for(int i=1,deg=0;i<=cnt;i++,deg=0)
	{
		if(used[i]) continue;
		for(int j=1;j<=cnt;j++)
			if(!used[j] && floyd[apr[j]][apr[i]]) deg++;
		if(deg==1)
		{
			printout[p]=apr[i],used[i]=1;
			dfs(p+1);
			used[i]=0;
		}
	}
}
int main()
{
	init();
	cover_relation();
	linkmap();
	for(int i=0;i<26;i++)
		if(discovered[i]) apr[++cnt]=i;
	dfs(0);
	return 0;
}
