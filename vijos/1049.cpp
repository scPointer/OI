#include <cstdio>
#include <cstring>
int n,m,k;
int command[11][101],cm[2][101];
int comch[11][101],ch[101];
int ans[101];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		cm[0][i]=i;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&command[i][j]);
			cm[i%2][j]=cm[1-i%2][command[i][j]];
			comch[i][command[i][j]]=j;
		}
	if(m%2==1)
		for(int i=1;i<=n;i++)
			cm[0][i]=cm[1][i];
	for(int i=1;i<=n;i++)
		ch[cm[0][i]]=i;
	for(int i=1;i<=n;i++)
	{
		int p=ch[i],round=1;
		int ki=k;
		while(p!=i)
		{
			p=ch[p];
			round++;
		}
		ki%=(round*m);
		while(ki>=m)
		{
			p=ch[p];
			ki-=m;
		}
		int j=0;
		while(ki>0)
		{
			p=comch[++j][p];
			ki--;
		}
		ans[p]=i;
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d",ans[i]);
		if(i!=n) printf(" ");
	}
	return 0;
}
