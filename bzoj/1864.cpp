#include <cstdio>
#define N 1000005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
int mn[2][N],mx[2][N];
int nds;
int RD()
{
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	return cr-'0';
}
int dfs()
{
	int np=++nds;
	int sons=RD();
	if(sons==0)
	{
		mn[0][np]=mx[0][np]=0;
		mn[1][np]=mx[1][np]=1;
	}
	else if(sons==1)
	{
		int ls=dfs();
		mn[0][np]=Min(mn[0][ls],mn[1][ls]);
		mn[1][np]=mn[0][ls]+1;
		mx[0][np]=Max(mx[0][ls],mx[1][ls]);
		mx[1][np]=mx[0][ls]+1;
	}
	else
	{
		int ls=dfs();
		int rs=dfs();
		mn[0][np]=Min(mn[0][ls]+mn[1][rs],mn[1][ls]+mn[0][rs]);
		mn[1][np]=mn[0][ls]+mn[0][rs]+1;
		mx[0][np]=Max(mx[0][ls]+mx[1][rs],mx[1][ls]+mx[0][rs]);
		mx[1][np]=mx[0][ls]+mx[0][rs]+1;
	}
	return np;
}
int main()
{
	dfs();
	printf("%d %d\n",Max(mx[0][1],mx[1][1]),Min(mn[0][1],mn[1][1]));
}