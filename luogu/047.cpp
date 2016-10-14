#include <cstdio>
#define MAXL 10005
bool tree[MAXL];
int main()
{
	int l,m;
	scanf("%d%d",&l,&m);
	for(int i=1;i<=m;i++)
	{
		int left,right;
		scanf("%d%d",&left,&right);
		for(int j=left;j<=right;j++)
			tree[j]=1;
	}
	int count=0;
	for(int i=0;i<=l;i++)
		if(tree[i]==0)
			count++;
	printf("%d",count);
	return 0;
}
