#include <cstdio>
#include <cstring>
#define MAXN 30
#define MAXM MAXN*MAXN
#define GETPOINT(a,b) ((a-1)*n+b)
#define MABS(a) (a>=0?(a):(a)*(-1))
//bool map[MAXN][MAXN];
bool map[MAXN*MAXN];
bool cmp[MAXM][MAXM];
int cr[MAXM];//coordinate
//int g[MAXM];//graph
//int e[MAXM*20],etop,head[MAXM],next[MAXM];

bool vis[MAXM];
int match[MAXM];
int l[MAXM],ltop;
//int r[MAXM],rtop,al[MAXM],ar[MAXM],bel[MAXM];
int n,m,k,ans;
int xa,ya,xb,yb;
void readpoint()
{
	char co[5];
	int pnum;
	scanf("%s",co);
	if(co[2]>='0' && co[2]<='9')
		pnum=(co[1]-'0')*10+(co[2]-'0');
	else pnum=co[1]-'0';
	map[GETPOINT(co[0]-'A'+1,pnum)]=1;
}
/*
void addedge(int p1,int p2)
{
	etop++;
	e[etop]=p2;
	next[etop]=head[p1];
	head[p1]=etop;
}
*/
bool trymatch(int p)
{
	for(int i=1;i<=m;i++)
	{
		if(cmp[p][i]==1 && vis[i]==0)
		{
			vis[i]=1;
			if(match[i]==0 || trymatch(match[i]) )
			{
				match[i]=p;
				return 1;
			}
		}
	}
	return 0;
}
/*bool trymatch(int p)
{
	for(int i=head[p];i!=0;i=next[i])
	{
		if(vis[e[i]]==0)
		{
			vis[e[i]]=1;
			if(match[e[i]]==0 || trymatch(match[e[i]]) )
			{
				match[e[i]]=p;
				return 1;
			}
		}
	}
	return 0;
}
*/
void devidemap()
{
	for(int i=1;i<=m;i++)
	{
		if(((cr[i]-1)/n+(cr[i]-1)%n)%2==0)
			l[++ltop]=i;
//		else r[++rtop]=i;
	}
//	for(int i=1;i<=rtop;i++) match[i]=0;
	for(int i=1;i<=ltop;i++)
	{
		memset(vis,0,sizeof(vis));
		if(trymatch(l[i])==1) ans++;
	}
}
bool can_attack(int a,int b)
{
	xa=(a-1)/n+1;
	ya=(a-1)%n+1;
	xb=(b-1)/n+1;
	yb=(b-1)%n+1;
	return MABS(xa-xb)!=0 && MABS(ya-yb)!=0 && MABS(xa-xb)+MABS(ya-yb)==3;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		readpoint();
//	initialization();
	
	for(int i=1;i<=n*n;i++)
		if(map[i]==1)
//			addpoint(++k,i);
			{
				cr[++k]=i;
//				g[i]=k;
			}
	for(int i=1;i<=m-1;i++)
		for(int j=i+1;j<=m;j++)
			if(can_attack(cr[i],cr[j])==1)
			{
				cmp[i][j]=cmp[j][i]=1;
//				addedge(i,j);
//				printf("addedge %d -> %d\n",i,j);
//				addedge(j,i);
			}
	devidemap();
	printf("%d",ans);
	return 0;
}
/*
void initialization()
{
	attack[0]=-2*n-1;attack[1]=-2*n+1;attack[2]=-n-2;attack[3]=-n+2;
	attack[4]=2*n-1;attack[5]=2*n+1;attack[6]=n-2;attack[7]=n+2;
	limit[1][0]=3;limit[1][1]=3;limit[1][2]=2;limit[1][3]=2;
	limit[1][4]=1;limit[1][5]=1;limit[1][6]=1;limit[1][7]=1;
	limit[2][0]=n;limit[2][1]=n;limit[2][2]=n;limit[2][3]=n;
	limit[2][4]=n-2;limit[2][5]=n-2;limit[2][6]=n-1;limit[2][7]=n-1;
	limit[3][0]=2;limit[3][1]=1;limit[3][2]=3;limit[3][3]=1;
	limit[3][4]=2;limit[3][5]=1;limit[3][6]=3;limit[3][7]=1;
	limit[4][0]=n;limit[4][1]=n-1;limit[4][2]=n;limit[4][3]=n-2;
	limit[4][4]=n;limit[4][5]=n-1;limit[4][6]=n;limit[4][7]=n-2;
}

void addpoint(int newpoint,int p)
{
//	cr[newpoint]=p;
	if(newpoint==9)
	{
		int st;
		st++;
	}
	g[p]=newpoint;
	for(int i=0;i<=7;i++)
		if((p-1)/n+1>=limit[1][i] && (p-1)/n+1<=limit[2][i]
			&& (p-1)%n+1>=limit[3][i] && (p-1)%n+1<=limit[4][i])
		{
			if(p+attack[i]>=1 && p+attack[i]<=n*n && g[p+attack[i]]!=0)
			{
				addedge(newpoint,g[p+attack[i]]);
				addedge(g[p+attack[i]],newpoint);
//				printf("addedge %d -> %d\n",g[p+attack[i]],newpoint);
//				printf("addedge %d -> %d\n",newpoint,g[p+attack[i]]);
			}
		}
}
void dfs(int p,int wer)
{
	vis[p]=1;
	if(wer==1)
	{
		l[++ltop]=p;
		al[p]=ltop;
		bel[p]=1;
	}
	else
	{
		r[++rtop]=p;
		ar[p]=rtop;
		bel[p]=2;
	}
	for(int i=head[p];i!=0;i=next[i])
		if(bel[e[i]]==0)
			dfs(e[i],3-bel[p]);
}
*/
