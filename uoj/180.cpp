#include <cstdio>
#define N 100050
#define Max(a,b) (a>b?a:b)
#define lowbit(x) (x&-x)
int n,maxp,tot;
int vis[N],au[N];
int a[N],b[N];
int ra[N],rb[N];

int B[N];
void add(int p,int v)
{
	for(;p<=n;p+=lowbit(p))
		B[p]=Max(B[p],v);
}
inline void Read(int& res)
{
	static char cr;
	while((cr=getchar())<'0' ||cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
}
int main()
{
	bool access=1;
	Read(n);
	for(int i=1;i<=n;i++) {Read(a[i]);ra[a[i]]=i;}
	for(int i=1;i<=n;i++) {Read(b[i]);rb[b[i]]=i;}
	
	maxp=n;
	long long linea=542,lineb=542;
	int st=1;
	for(int i=1;i<=n;i++)
	{
		linea+=(a[i]*a[i]+26467761);
		lineb+=(b[i]*b[i]+26467761);
		if(linea==lineb)
		{
			++tot;
			for(int j=st;j<=i;j++)
				vis[a[j]]=tot;
			maxp=n;
			for(int j=i;j>=st;j--)
			{
//				while(vis[maxp]!=tot) maxp--;
				int p=ra[b[j]];
				vis[a[p]]=-1;
//				if(j==p) continue;
				for(int k=p+1;k<=i;k++)
					if(vis[a[k]]==tot && a[k]>a[p])
					{
						access=0;break;
					}
				if(!access) break;
			}
			st=i+1;
		}
	}
	if(access) printf("YES");
	else printf("NO");
	return 0;
}
