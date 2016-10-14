#include <cstdio>
#define N 8005
inline int RD()
{
	static int res;
	static char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
int vis[N<<1];
int a[N],n;
int solve(int p)
{
	int res=0;
	for(int i=0;i<=(n<<1);i++) vis[i]=0;
	for(int i=p,ptr=n;i>=1;i--)
	{
		if(a[i]>a[p]) ptr++;
		if(a[i]<a[p]) ptr--;
		vis[ptr]++;
	}
	for(int i=p,ptr=n;i<=n;i++)
	{
		if(a[i]<a[p]) ptr++;
		if(a[i]>a[p]) ptr--;
		res+=vis[ptr];
	}
	return res;
}
int main()
{
	n=RD();
	for(int i=1;i<=n;i++) a[i]=RD();
	for(int i=1;i<=n;i++)
		printf("%d ",solve(i));
}