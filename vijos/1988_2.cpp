#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define INF 100000009
using namespace std;
int n,ans=0;
int sc[300005];
int dp[300005][20];
int getlen(int x) {
    int ans=0;
    while (1<<ans <= x) {
        ++ans;
    }
    return ans-1;
}
int query(int l,int r) {
    if (r<l)
        return -INF;
    int len=getlen(r-l+1);
    return max(dp[l][len],dp[r-(1<<len)+1][len]);
}
int main() {
	freopen("p1988.in","r",stdin);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",sc+i);
    sort(sc+1,sc+n+1);
    for (int i=1;i<=n;i++) {
        sc[i]+=(n-i);
        dp[i][0]=sc[i];
    }
    for (int k=1,t=2;t <= n;k++,t<<=1) {
        for (int i=1,end=n-t+1;i<=end;i++) {
            dp[i][k]=max(dp[i][k-1],dp[i+(1<<(k-1))][k-1]);
        }
    }
    for (int i=1;i<=n;i++) {
        if (query(i+1,n) <= sc[i]+i-1)
            ans++;
    }
    printf("%d",ans);
    return 0;
}