#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define error(x) (!(x)?puts("error"):0)
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
 
 
const int N=102, M=N*60, Q=M+M, MD=10007;
int c[M][26], tot, w[M], q[M], fail[M], n, f[N][M];
void add(char *s) {
    int len=strlen(s), now=0;
    rep(i, len) {
        int t=s[i]-'A';
        if(!c[now][t]) c[now][t]=++tot;
        now=c[now][t];
    }
    w[now]=1;
}
void bfs() {
    int now=0, front=0, tail=0;
    q[tail++]=now;
    while(front!=tail) {
        now=q[front++]; if(front==Q) front=0;
        rep(y, 26) if(c[now][y]) {
            q[tail++]=c[now][y]; if(tail==Q) tail=0;
            if(now==0) continue;
            int t=fail[now];
            while(t && !c[t][y]) t=fail[t];
            fail[c[now][y]]=c[t][y];
            if(w[c[t][y]]) w[c[now][y]]=1; //这里。。。。。。。。。
        }
    }
}
void P(int &a, const int &b) { a=(a+b)%MD; }
int work() {
    int ret=0;
    // rep(i, 26) { //一开始我这样写的，可以对，从i=1开始就行了
    //  if(!c[0][i]) f[1][0]++;
    //  else if(!w[c[0][i]]) f[1][c[0][i]]=1;
    // }
    f[0][0]=1; //这是后边看了题解后才焕然大雾。。
    for1(i, 0, n) for1(j, 0, tot) if(f[i][j]) {
        rep(y, 26) {
            int t=j;
            while(t && !c[t][y]) t=fail[t];
            t=c[t][y];
            if(!w[t]) P(f[i+1][t], f[i][j]);
        }
    }
    for1(i, 0, tot) if(!w[i]) P(ret, f[n][i]);
    int all=1;
    for1(i, 1, n) all*=26, all%=MD;
    ret=((all-ret)%MD+MD)%MD;
    return ret;
}
int main() {
    int m=getint(); read(n);
    char s[N];
    for1(i, 1, m) { scanf("%s", s); add(s); }
    bfs();
    print(work());
    return 0;
}