#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>	
#define MAXN 100010
#define RG register
#define lowbit(i) ((i) & -(i))
#define cmax(a, b) (a < (b) ? a = (b), 1 : 0)
int n, A[MAXN], B[MAXN];
int T[MAXN];
inline int Read();
inline void modify(RG int i, RG int v)
{
	for(; i <= n; i += lowbit(i))
		cmax(T[i], v);
}
inline int query(RG int i)
{
	RG int ans = 0;
	for(; i; i -= lowbit(i))
		cmax(ans, T[i]);
	return ans;
}
int main()
{
	n = Read();
	for(RG int i = 1; i <= n; ++i) A[Read()] = i;
	for(RG int i = 1; i <= n; ++i) B[Read()] = i;
	for(RG int i = 1; i <= n; ++i)
	{
		if(query(A[i]) > B[i]){puts("NO");return 0;}
/*lgg*/printf("i = %d A = %d B = %d query = %d\n", i, A[i], B[i], query(A[i]));
		
		modify(A[i], B[i]);
//		for(int j=1;j<=n;j++) printf("%d ",T[j]);
//		printf("\n");
	}
	puts("YES");
}
inline int Read()
{
	static char cr;
	static int res;
	while((cr=getchar())<'0' ||cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}