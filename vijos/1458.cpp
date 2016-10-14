#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 10005
#define BITS 2000
int n,m;

char rname[MAXN][258];
char name[MAXN][258];
int st[MAXN];

int bigint[3][BITS];
int cmp(int a,int b)
{
	if(strcmp(rname[b],rname[a])<0) return 0;
	else return 1;
}
void add(int* a,int* b,int* c)
{
	for(int i=0;i<BITS;i++)
		c[i]=a[i]+b[i];
	for(int i=0;i<BITS-1;i++)
		if(c[i]>=100000000)
		{
			c[i+1]+=c[i]/100000000;
			c[i]%=100000000;
		}
}
void solve2()
{
	memset(bigint,0,sizeof(bigint));
	bigint[0][0]=1;
	bigint[1][0]=2;
	bigint[2][0]=3;
	int i=3;
	if(i<m)
		while(i<=m)
		{
			add(bigint[1],bigint[2],bigint[0]);
			if(++i==m) break;
			add(bigint[0],bigint[2],bigint[1]);
			if(++i==m) break;
			add(bigint[0],bigint[1],bigint[2]);
			if(++i==m) break;
		}
	else i=m;
	i=(i+2)%3;
	int heightbit=BITS-1;
	while(bigint[i][heightbit]==0) heightbit--;
	printf("%d",bigint[i][heightbit--]);
	while(heightbit>=0)
		printf("%08d",bigint[i][heightbit--]);
}
void solve1()
{
	int ans1=0;
	for(int i=0;i<m;i++)
	{
		char s[258];
		scanf("%s",s);
		int l=-1,r=n,mid;
		while(l<r-1)
		{
			mid=(l+r)/2;
			int ret=strcmp(s,name[mid]);
			if(ret>0) l=mid;
			else r=mid;
		}
		if(l<n-1) l++;
		int len=strlen(s);
		int j;
		for(j=0;j<len;j++)
			if(s[j]!=name[l][j]) break;
		if(j==len)
		{
			ans1++;
//			printf("%s\n",s);
		}
	}
	printf("%d\n",ans1);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n-1;i++)
		scanf("%s",rname[i]);
	for(int i=0;i<=n-1;i++)
		st[i]=i;
	sort(st,st+n,cmp);
	for(int i=0;i<=n-1;i++)
		strcpy(name[i],rname[st[i]]);
	solve1();
	solve2();
	return 0;
}
