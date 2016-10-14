/**************************************************************
    Problem: 4003
    User: rausen
    Language: C++
    Result: Accepted
    Time:6872 ms
    Memory:56988 kb
****************************************************************/
 
#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;
typedef double lf;
typedef long long ll;
 
const int N = 3e5 + 5;
 
struct edge {
    int next, to;
    edge(int _n = 0, int _t = 0) : next(_n), to(_t) {}
} e[N];
 
struct heap {
    heap *ls, *rs;
    ll v, tag_t, tag_a;
    int dep, st, w;
     
    void* operator new(size_t, int x, int y, ll z) {
        static heap mempool[N], *c = mempool;
        c -> ls = c -> rs = NULL;
        c -> dep = 1, c -> v = z, c -> w = x, c -> st = y;
        c -> tag_t = 1, c -> tag_a = 0;
        return c++;
    }
     
    inline void Times(ll x) {
        v *= x, tag_t *= x, tag_a *= x;
    }   
    inline void Add(ll x) {
        v += x, tag_a += x;
    }   
    inline void push() {
        if (ls) ls -> Times(tag_t);
        if (rs) rs -> Times(tag_t);
        tag_t = 1;
        if (ls) ls -> Add(tag_a);
        if (rs) rs -> Add(tag_a);
        tag_a = 0;
    }
     
    #define Dep(p) (p ? p -> dep : 0)
    inline void update() {
        dep = Dep(rs) + 1;
    }
         
    friend heap* merge(heap *x, heap *y) {
        if (!x) return y;
        if (!y) return x;
        if (x -> v > y -> v) swap(x, y);
        x -> push();
        x -> rs = merge(x -> rs, y);
        if (Dep(x -> rs) > Dep(x -> ls)) swap(x -> ls, x -> rs);
        x -> update();
        return x;
    }
    #undef Dep
     
    inline heap* pop() {
        this -> push();
        return merge(ls, rs);
    }
} *h[N];
 
struct tree_node {
    int fa, a, dep;
    ll h, v;
} tr[N];
 
inline ll read() {
    static ll x, sgn;
    static char ch;
    x = 0, sgn = 1, ch = getchar();
    while (ch < '0' || '9' < ch) {
        if (ch == '-') sgn = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return sgn * x;
}
 
int n, m;
int first[N], tot;
int ans1[N], ans2[N];
 
inline void add_edge(int x, int y) {
    e[++tot] = edge(first[x], y);
    first[x] = tot;
}
 
#define y e[x].to
void dfs(int p) {
    int x;
    tr[p].dep = tr[tr[p].fa].dep + 1;
    for (x = first[p]; x; x = e[x].next) {
        dfs(y);
        h[p] = merge(h[p], h[y]);
    }
    while (h[p] && h[p] -> v < tr[p].h) {
        ++ans1[p], ans2[h[p] -> w] = tr[h[p] -> st].dep - tr[p].dep;
        h[p] = h[p] -> pop();
    }
    if (h[p])
        if (tr[p].a) h[p] -> Times(tr[p].v);
        else h[p] -> Add(tr[p].v);
}
#undef y
 
int main() {
	freopen("4003.in","r",stdin);
    int i, x, c;
    ll s;
    n = read(), m = read();
    for (i = 1; i <= n; ++i) tr[i].h = read();
    for (i = 2; i <= n; ++i) {
        x = read(), add_edge(x, i);
        tr[i].fa = x    , tr[i].a = read(), tr[i].v = read();
    }
    for (i = 1; i <= m; ++i) {
        s = read(), c = read();
        h[c] = merge(h[c], new(i, c, s)heap);
    }
    dfs(1);
    while (h[1]) {
        ans2[h[1] -> w] = tr[h[1] -> st].dep;
        h[1] = h[1] -> pop();
    }
	int ra=0;
	for (i = 1; i <= n; ++i)
		ra^=ans1[i];
//		printf("%d\n", ans1[i]);
    for (i = 1; i <= m; ++i)
		ra^=ans2[i];
//		printf("%d\n", ans2[i]);
	printf("%d\n",ra);
    return 0;
}