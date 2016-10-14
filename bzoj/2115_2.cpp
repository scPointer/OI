//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 50//010
#define M 200//010
typedef long long ll;
struct Edge{
    int to, next;
    ll w;
}edge[M];

int cnt, h[N], n, m;

void add(int u, int v, ll w){
    cnt ++;
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = h[u];
    h[u] = cnt;
    swap(u, v);
    cnt ++;
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = h[u];
    h[u] = cnt;
}

ll d[N], a[M], num;

bool vis[N];

void dfs(int x){
    vis[x] = 1;
    for(int i = h[x]; i; i = edge[i].next){
        int y = edge[i].to;
        if(!vis[y]) d[y] = d[x] ^ edge[i].w, dfs(y);
        else a[++ num] = d[y] ^ d[x] ^ edge[i].w;
    }
}

int gauss(){
    int k = 1;
    for(int p = 63; p >= 0; p --){
        int t = 0;
        for(int i = k; i <= num; i ++)
            if(a[i] >> p & 1){t = i; break;}
        if(t){
            swap(a[t], a[k]);
            for(int i = 1; i <= num; i ++)
                if(i != k && (a[i] >> p & 1))
                    a[i] ^= a[k];
            k ++;
        }
    }
    return k - 1;
}

int main(){
    scanf("%d%d", &n, &m);
    int u, v; ll w;
    for(int i = 1; i <= m; i ++){
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
    }
    dfs(1);
    int cnt = gauss();
    ll ans = d[n];
    for(int i = 1; i <= cnt; i ++)
        if((ans ^ a[i]) > ans)
            ans ^= a[i];
    printf("%lld\n", ans);
    return 0;
}