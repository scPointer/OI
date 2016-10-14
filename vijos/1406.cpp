#include <cstdio>
#define MAXN 21
#define MAXL 405
#define MAXINT 500
int map[MAXN][MAXN];
int rmap[MAXN][MAXN];
int fl[MAXL][MAXL];
int m,n;

int ptop;
int queuex[MAXN*MAXN];
int queuey[MAXN*MAXN];
void init()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		char s1[MAXN+5];
		scanf("%s",s1);
		for(int j=0;j<=n-1;j++)
			if(s1[j]>='A'&&s1[j]<='Z')
				map[i][j+1]=s1[j]-'A'+1;
	}
}
void fset()
{
	for(int i=0;i<=MAXL-1;i++)
		for(int j=0;j<=MAXL-1;j++)
			fl[i][j]=MAXINT;
}
void addblock(int x0,int y0)
{
	
	int letter=map[x0][y0];
	int st,ed;
	queuex[st=ed=1]=x0;
	queuey[st]=y0;
	map[x0][y0]=-1;
	while(ed<=st)
	{
		int qx=queuex[ed],qy=queuey[ed];
		if(qx+1<=m&&map[qx+1][qy]==letter)
		{queuex[++st]=qx+1;queuey[st]=qy;map[qx+1][qy]=-1;}
		if(qx-1>=1&&map[qx-1][qy]==letter)
		{queuex[++st]=qx-1;queuey[st]=qy;map[qx-1][qy]=-1;}
		if(qy+1<=n&&map[qx][qy+1]==letter)
		{queuex[++st]=qx;queuey[st]=qy+1;map[qx][qy+1]=-1;}
		if(qy-1>=1&&map[qx][qy-1]==letter)
		{queuex[++st]=qx;queuey[st]=qy-1;map[qx][qy-1]=-1;}
		ed++;
	}
	ptop++;
	for(int i=1;i<=st;i++)
		rmap[queuex[i]][queuey[i]]=ptop;
}
int main()
{
	init();
	fset();
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(map[i][j]>0)
				addblock(i,j);
				
	ptop++;
	for(int i=1;i<=n;i++)
		fl[rmap[1][i]][ptop]=fl[ptop][rmap[1][i]]=1;
	ptop++;
	for(int i=1;i<=n;i++)
		fl[rmap[m][i]][ptop]=fl[ptop][rmap[m][i]]=1;
	
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n-1;j++)
			fl[rmap[i][j]][rmap[i][j+1]]=fl[rmap[i][j+1]][rmap[i][j]]=1;
	for(int i=1;i<=m-1;i++)
		for(int j=1;j<=n;j++)
			fl[rmap[i+1][j]][rmap[i][j]]=fl[rmap[i][j]][rmap[i+1][j]]=1;
	for(int k=1;k<=ptop;k++)
		for(int i=1;i<=ptop;i++)
			for(int j=1;j<=ptop;j++)
				if(fl[i][k]+fl[k][j]<fl[i][j])
					fl[i][j]=fl[i][k]+fl[k][j];
	printf("%d",fl[ptop-1][ptop]-1);
	return 0;
}
