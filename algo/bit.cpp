//1-indexed
#define lowbit(x) (x&(-x))
#define N
namespace bit{

ll mp[N];
int n;
void add(int x,int val)
{
	for(;x<=n;x+=lowbit(x))
			mp[x]+=val;
}
ll sum(int x)
{
	ll res=0;
	for(;x;x-=lowbit(x))
			res+=mp[x];
	return res;
}

}

#define lowbit(x) (x&(-x))
namespace bitd{

ll mp[N][N];
int n,m;
void add(int x,int y,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			mp[i][j]+=val;
}
ll sum(int x,int y)
{
	ll res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=mp[i][j];
	return res;
}

}