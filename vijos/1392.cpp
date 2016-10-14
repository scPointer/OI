#include <cstdio>
#define MAXN 1005
#define INF 1050
#define MIN(a,b) (a<=b?a:b)
struct Node{
	int s,p;
	bool operator<=(Node& oth){return s<oth.s || (s==oth.s && p<=oth.p);}
}node[MAXN][MAXN];
int w[MAXN];
int n,m,t;
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=0;i<=n;i++)
		for(int j=1;j<=n;j++)
			node[i][j]=(Node){INF,0};
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			Node temp=node[i-1][j-1];
			if(temp.p+w[i]<=t)
			{
				temp.p+=w[i];
			}
			else
			{
				temp.s++;temp.p=w[i];
			}
			node[i][j]=MIN(node[i-1][j],temp);
		}
	int ans=0;
	Node limit=(Node){m,0};
	for(int i=n;i>=1;i--)
		if(node[n][i]<=limit)
		{
			ans=i;
			break;
		}
	printf("%d",ans);
	return 0;
}
