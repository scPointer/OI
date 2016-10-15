#include <cstdio>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9')
		if(cr=='.') break;
	return cr=='.'? -1:cr-'0';
}
int a[200005];
int main()
{
	int n,t;scanf("%d%d",&n,&t);
	int pos=-1;
	for(int i=1;i<=n;i++)
	{
		a[i]=RD();
		if(a[i]==-1) pos=i;
	}
	if(pos==-1)
	{
		for(int i=1;i<=n;i++)
			printf("%d",a[i]);
		return 0;
	}
	for(int i=pos+1;i<=n;i++)
		if(a[i]>=5)
		{
			int j=i;
			while(t>0 && j>pos && a[j]>=5)
			{
				a[j]=-2;
				if(j-1>pos) a[j-1]+=1;
				else a[j-2]+=1;
				j--;t--;
			}
			j=pos-1;
			while(j>0 && a[j]>=10)
			{
				a[j-1]+=1;
				a[j]=0;
				j--;
			}
			break;
		}
	if(a[0]>0) printf("%d",a[0]);
	for(int i=1;i<=n;i++)
		if(a[i]==-2) break;
		else if(a[i]==-1)
		{
			if(i+1<=n && a[i+1]!=-2) printf(".");
		}
		else printf("%d",a[i]);
}
