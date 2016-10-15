#include <cstdio>
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
int main()
{
	int L,n;scanf("%d%d",&L,&n);
	int mn=0,mx=0;
	for(int i=1,pos;i<=n;i++)
	{
		scanf("%d",&pos);
		mn=Max(mn,Min(pos,L-pos+1));
		mx=Max(mx,Max(pos,L-pos+1));
	}
	printf("%d %d",mn,mx);
}
