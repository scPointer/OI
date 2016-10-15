#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 100005
#define Min(a,b) (a<b?a:b)
int pos[N];
int calc(int l,int r,int a)
{
	return abs(r-l)+std::min(abs(a-l),abs(a-r));
}
int main()
{
	int n,a;
	scanf("%d%d",&n,&a);
	for(int i=1;i<=n;i++)
		scanf("%d",&pos[i]);
	std::sort(pos+1,pos+1+n);
	if(n==1){printf("0");return 0;}
	long long ans=std::min(calc(pos[1],pos[n-1],a),calc(pos[2],pos[n],a));
	printf("%d",ans);
}
