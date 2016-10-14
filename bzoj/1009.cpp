#include <cstdio>
#define N 155
#define M 25
int mtx[N][M][M];
int n,m,mo;
int line[M],last[M];
void kmp()
{
	last[0]=-1;
	for(int i=1,j;i<=m;i++)
	{
		j=last[i-1];
		while(j!=-1 && line[j+1]!=line[i])
			j=last[j];
		last[i]= j==-1?0:j+1;
	}
}
void print(int f)
{
	printf("mtx%d\n",f);
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=m;j++)
			printf("%d ",mtx[f][i][j]);
		printf("\n");
	}
}
void calc(int p1,int p2,int f)
{
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=m;k++)
				mtx[f][i][j]+=mtx[p1][i][k]*mtx[p2][k][j];
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			mtx[f][i][j]%=mo;
}
void cpy(int p,int f)
{
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			mtx[f][i][j]=mtx[p][i][j];
}
int fastmult(int n)
{
	int cnt=0;
	for(int i=1,j=2;j<=n;i++,j<<=1)
		calc(i-1,i-1,i),cnt++;
//	for(int i=0;i<=2;i++) print(i);
	bool iffirst=1;
	for(int i=0,j=1;j<=n;i++,j<<=1)
		if(n&j)
		{
			if(iffirst)
			{
				iffirst=0;
				cpy(i,++cnt);
			}
			else
			{
				calc(cnt,i,cnt+1);
				cnt++;
			}
		}
	return mtx[cnt][0][m];
}
int fastmult2(int d,int f)
{
	int res=1,mult=d%mo;
	while(f>0)
	{
		if(f%2==1) res=(res*mult)%mo;
		mult=(mult*mult)%mo;
		f/=2;
	}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&m,&mo);
	char cr;line[0]=-1;
	for(int i=1;i<=m;i++)
	{
		while( (cr=getchar())<'0' || cr>'9');
		line[i]=cr-'0';
	}
	kmp();
	for(int i=0,p;i<m;i++)
		for(int j=0;j<=9;j++)
		{
			p=i;
			while(p!=-1 && line[p+1]!=j) p=last[p];
			++p;
			mtx[0][i][p]++;
			mtx[0][i][p]%=mo;
		}
	mtx[0][m][m]=10;
	int ans=fastmult(n);
	int ans2=fastmult2(10,n);
	ans=((ans2-ans)%mo+mo)%mo;
	printf("%d",ans);
}
