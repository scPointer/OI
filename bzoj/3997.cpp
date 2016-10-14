#include <cstdio>
#include <algorithm>
using namespace std;
int d[1001][1001];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=m; ++j) {
                scanf("%d", &d[i][j]);
            }
        }
        for(int i=1; i<=n; ++i) {
            for(int j=m; j>=1; --j) {
                d[i][j]=max(d[i][j]+d[i-1][j+1], max(d[i][j+1], d[i-1][j]));
            }
        }
        printf("%d\n", d[n][1]);
    }
    return 0;
}