#include <cstdio>
#include <cstring>
#define MAXN 105
#define MAXM 1000005
#define MAXL 10005
#define milmod(a,b,c) (((a*(b/1000))%c*1000+(a*(b%1000))%c)%c)
#define max(a,b) (a>b?a:b)
int n,m;
char sa[MAXN][MAXL];
int xs[MAXN];
bool ans[MAXM];
bool check(int x,int mo)
{
	int rez=xs[0]%mo;
	int tx=1;
	for(int i=1;i<=n;i++)
	{
		tx=(x*tx)%mo;
		rez+=(xs[i]*tx)%mo;
	}
	return rez==0;
}
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
		scanf("%s",sa[i]);
	for(int i=0;i<=n;i++)
	{
		int fs;
		fs= sa[i][0]=='-'?1:0;
		int len=strlen(sa[i]);
		for(int j=max(len-4,fs);j<=len-1;j++)
			xs[i]=xs[i]*10+sa[i][j]-'0';
		if(fs==1) xs[i]*=-1;
	}
}
int main()
{
//	freopen("equation.in","r",stdin);
//	freopen("equation.out","w",stdout);
	init();
//	for(int kp=0;kp<=10;kp++)
	{
//		int mo=cmo[kp];
		int mo=10000;
		for(int i=1;i<=mo&&i<=m;i++)
			if(check(i,mo)==0)
				for(int j=i;j<=m;j+=mo)
					ans[j]=1;
	}
	for(int i=1;i<=m;i++)
		if(check(i,m)==0)
			ans[i]=1;
	int sum=0;
	for(int i=1;i<=m;i++)
		if(ans[i]==0) sum++;
	printf("%d\n",sum);
	for(int i=1;i<=m;i++)
		if(ans[i]==0) printf("%d\n",i);
	return 0;
}
