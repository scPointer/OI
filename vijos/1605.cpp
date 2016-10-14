#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1005
struct Edge{
	int pto;
	int next;
}ed[MAXN*MAXN*2];
int head[MAXN],edtop;
int color[MAXN];

int n;
int a[MAXN];
int res[MAXN];
int lamin[MAXN];
bool against[MAXN][MAXN];

int instack[MAXN];
void addedge(int p1,int p2)
{
	edtop++;
	ed[edtop].pto=p2;
	ed[edtop].next=head[p1];
	head[p1]=edtop;
}
bool draw(int p,int cl)
{
	color[p]=cl;
	int k=head[p];
	while(ed[k].pto!=0)
	{
		if(color[ed[k].pto]==0)
		{
			if(draw(ed[k].pto,3-cl)==0) return 0;
		}
		else if(color[ed[k].pto]==cl) return 0;
		k=ed[k].next;
	}
	return 1;
}
void print()
{
	int out=1;
	int count=0;
	for(int i=1;i<=n;i++)
	{
		instack[a[i]]=color[i];
		if(color[i]==1) printf("a");
		else printf("c");
		count++;
//	if(count<2*n)
			printf(" ");
		while(out<=n&&instack[out]>0)
		{
			if(instack[out]==1) printf("b");
			else printf("d");
			count++;
			if(count<2*n) printf(" ");
			out++;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		res[a[i]]=i;
	}
	lamin[n]=a[n];
	for(int i=n-1;i>=1;i--)
		lamin[i]=min(a[i],lamin[i+1]);
	for(int i=1;i<=n-2;i++)
		for(int j=i+1;j<=n-1;j++)
			if(a[i]<a[j]&&lamin[j+1]<a[i])
			{
				addedge(i,j);
				addedge(j,i);
				against[i][j]=against[j][i]=1;
			}
	for(int i=1;i<=n;i++)
		if(color[i]==0)
			if(draw(i,1)==0)
			{
				printf("0");
				return 0;
			}
	print();
	return 0;
}
