#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 1005
long long ans[MAXN][MAXN];
long long l[MAXN],m[MAXN];
int n,lo,hi;
int main()
{
	scanf("%d%d%d",&n,&lo,&hi);
	memset(ans,0,sizeof(ans));
	l[0]=m[0]=0;
	for(int i=1;i<=n;i++) cin>>l[i];
	for(int i=1;i<=n;i++) cin>>m[i];
	for(int i=1;i<=n;i++) l[i]+=l[i-1];
	for(int i=1;i<=n;i++) m[i]+=m[i-1];
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			ans[i][j]=max(ans[i-1][j],ans[i][j-1]);
			if(l[j]-l[i-1]>=lo&&l[j]-l[i-1]<=hi)
					ans[i][j]=max(ans[i][j],ans[i-1][j-1]+(m[j]-m[i-1]));
		}
	cout<<ans[n][n];
	return 0;
}
