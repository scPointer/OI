#include <cstdio>
#include <ctime>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
int main()
{
	freopen("x.in","r",stdin);
	int c1=clock();
	int n=RD();
	for(int i=1,p;i<=n;i++)
		p=RD();
	printf("%d\n",clock()-c1);
}