#include <cstdio>
#include <algorithm>
using namespace std;
#define N 30//0005
#define Max(a,b) (a>b?a:b)
int score[N];
inline int RD()
{
	static char cr;
	static int res;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int main()
{
//	freopen("p1988.in","r",stdin);
	int n=RD();
	for(int i=1;i<=n;i++) score[i]=RD();
	sort(score+1,score+1+n);
	int dmax=score[n]+1,ans=1;
	for(int i=n-1;i>=1;i--)
	{
		if(dmax<=score[i]+n) ans++;
		dmax=Max(dmax,score[i]+n-i+1);
	}
	printf("%d",ans);
}
