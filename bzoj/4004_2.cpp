/**************************************************************
    Problem: 4004
    User: rausen
    Language: C++
    Result: Accepted
    Time:812 ms
    Memory:2840 kb
****************************************************************/
 
#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;
typedef double lf;
const int N = 13;//505;
 
inline int read() {
    static int x;
    static char ch;
    x = 0, ch = getchar();
    while (ch < '0' || '9' < ch)
        ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
 
template <class T> int sgn(T x) {
    static T eps = 1e-5;
    if (fabs(x) < eps) return 0;
    return eps > 0 ? 1 : -1;
}
 
struct data {
    int c;
    lf v[N];
     
    inline lf& operator [] (int i) {
        return v[i];
    }
     
    inline void get(int m) {
        static int i;
        for (i = 1; i <= m; ++i) v[i] = read();
    }
     
    inline bool operator < (const data &p) const {
        return c < p.c;
    }
} a[N];
 
int n, m;
int w[N], ans1, ans2;
 
int main() {
	freopen("4004.in","r",stdin);
    int i, j, k;
    lf tmp;
    n = read(), m = read();
    for (i = 1; i <= n; ++i) a[i].get(m);
    for (i = 1; i <= n; ++i) a[i].c = read();
    sort(a + 1, a + n + 1);
     
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j) if (sgn(a[i][j]) == 1) {
            if (w[j]) {
                tmp = a[i][j] / a[w[j]][j];
                for (k = j; k <= m; ++k) a[i][k] -= tmp * a[w[j]][k];
            } else {
                w[j] = i;
                ++ans1, ans2 += a[i].c  ;
                break;
            }
        }
    printf("%d %d\n", ans1, ans2);
    return 0;
}