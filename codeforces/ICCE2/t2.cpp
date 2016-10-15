#include <cstdio>
int a[55][55];
int n,m;
bool check()
{
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		for(int j=1;j<=m;j++)
			if(a[i][j]!=j) cnt++;
		if(cnt>2) return 0;
	}
	return 1;
}
void doswap(int x,int y)
{
	for(int i=1;i<=n;i++)
	{
		int t=a[i][x];
		a[i][x]=a[i][y];
		a[i][y]=t;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	if(check()) {puts("YES");return 0;}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
		{
			doswap(i,j);
			if(check()) {puts("YES");return 0;}
			doswap(i,j);
		}
	puts("NO");
}
