#include <cstdio>
#include <cstring>
#define N 6050
#define MO 10007
#define root 1
int nxt[N][27];
int val[N],fa[N],fail[N];
bool reach[N];
int nds;
int dp[N][2];
char rd[N];
int addNode(int p,int v)
{
	if(nxt[p][v]) return nxt[p][v];
	else{
		nxt[p][v]=++nds;
		val[nds]=v;fa[nds]=p;
		return nds;
	}
}
void setAho(int n)
{
	nds=1;
	for(int i=1,len,j,p;i<=n;i++)
	{
		scanf("%s",rd);
		while(rd[0]=='\n') scanf("%s",rd);
		len=strlen(rd);
		for(j=0,p=root;j<len;j++)
			if(rd[j]<'A' || rd[j]>'Z') break;
			else p=addNode(p,rd[j]-'A'+1);
		reach[p]=1;
	}
}
int q[N];
void setFail()
{
	int l=1,r=0,p,f,pv;
	for(int i=1;i<=26;i++)
		if(nxt[root][i]) q[++r]=nxt[root][i];
	while(l<=r)
	{
		p=q[l++];
		pv=val[p];
		f=fail[fa[p]];
		while(f && nxt[f][pv]==0) f=fail[f];
		fail[p]= f? nxt[f][pv]: root;
		if(reach[fail[p]]==1) reach[p]=1;//套路真深..
		for(int i=1;i<=26;i++)
			if(nxt[p][i]) q[++r]=nxt[p][i];
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	setAho(n);
	setFail();
	for(int i=1,p;i<=nds;i++)
		if(reach[i]==0)
		{
			for(int j=1;j<=26;j++)
			{
				p=i;
				while(p && nxt[p][j]==0) p=fail[p];
				nxt[i][j]= p? nxt[p][j]: root;
			}
		}
		else
		{
			for(int j=1;j<=26;j++)
				nxt[i][j]=i;
		}
	int x=0;
	dp[root][x]=1;
	for(int i=1;i<=m;i++)
	{
		x^=1;
		for(int p=1;p<=nds;p++)
			dp[p][x]=0;
		for(int p=1;p<=nds;p++)
			for(int j=1;j<=26;j++)
				dp[nxt[p][j]][x]=(dp[nxt[p][j]][x]+dp[p][x^1])%MO;
	}
	int ans=0;
	for(int p=1;p<=nds;p++)
		if(reach[p])
			ans=(ans+dp[p][x])%MO;
	printf("%d",ans);
}
