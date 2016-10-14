#include <cstdio>
#include <cstring>
#define N 205
#define lowbit(x) (x&(-x))
int nb[4];
int mtx[1<<9];
int dp[N][N];
char s[N];
inline int getb(char c)
{
	if(c=='W') return 1;
	else if(c=='I') return 2;
	else if(c=='N') return 4;
	else return 8;
}
inline void outc(int p)
{
	if(p&1) putchar('W');
	if(p&2) putchar('I');
	if(p&4) putchar('N');
	if(p&8) putchar('G');
	if(p==0) printf("The name is wrong!");
}
int main()
{
	for(int i=0;i<4;i++) scanf("%d",&nb[i]);
	for(int i=0,p;i<4;i++)
		for(int j=1;j<=nb[i];j++)
		{
			scanf("%s",s);
			p=(getb(s[0])<<4) | getb(s[1]);
//			printf("p=%d\n",p);
			mtx[p]|=(1<<i);
		}
	for(int i=0,p;i<(1<<8);i++)
	{
		p=i-lowbit(i);
		mtx[i]|=mtx[p];
		mtx[i]|=mtx[p-lowbit(p)+lowbit(i)];
		mtx[i]|=mtx[lowbit(i) | lowbit(p)];
//		if(mtx[i]!=0)
//			printf("%d,%d = %d\n",i/16,i%16,mtx[i]);
	}
	scanf("%s",s);
	int len=strlen(s);
	for(int i=1;i<=len;i++) dp[i][i]=getb(s[i-1]);
	for(int k=2;k<=len;k++)
		for(int i=1,j=k; j<=len; i++,j++)
			for(int l=i;l<=j-1;l++)
				dp[i][j]|=mtx[(dp[i][l]<<4) | dp[l+1][j]];
	outc(dp[1][len]);
}
