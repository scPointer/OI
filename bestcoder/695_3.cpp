#include <cstdio>
#include <algorithm>
#define N 1005
inline int Readint()
{
	static char cr;
	static int res;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
unsigned int ip[N],address[N];
int main()
{
	int T; scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		printf("Case #%d:\n",i);
		int n,m; scanf("%d%d",&n,&m);
		for(int j=1;j<=n;j++)
		{
			ip[j]=0;
			for(int k=3;k>=0;k--)
				ip[j]|=(Readint()<<(k*8));
		}
		
		for(int j=1;j<=m;j++)
		{
			unsigned int cover=0,cnt=0;
			for(int k=3;k>=0;k--)
				cover|=(Readint()<<(k*8));
				
			for(int k=1;k<=n;k++)
				address[k]=ip[k]&cover;
			std::sort(address+1,address+1+n);
			
			for(int k=1;k<=n;k++)
				if(k==1 || address[k]!=address[k-1])
					cnt++;
			printf("%d\n",cnt);
		}
	}
}