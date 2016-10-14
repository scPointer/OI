//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
using namespace std;
typedef double lf;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
#define pb push_back
inline int ri() {
	int x=0, f=1, c=getchar();
	for(; c<48||c>57; f=c=='-'?-1:f, c=getchar());
	for(; c>47&&c<58; x=x*10+c-48, c=getchar());
	return x*f;
}
ll d[15][3][10][4];
int num[15];
ll dfs(int x, int a, int b, int len, bool first, bool line) {
	if(!x) {
		return len==3;
	}
	if(!line && !first && d[x][a][b][len]!=-1) {
		return d[x][a][b][len];
	}
	ll tot=0;
	for(int i=0, g=line?num[x]:9; i<=g; ++i) {
		if(first && i==0) {
			tot+=dfs(x-1, 0, 0, 0, first, line && i==g);
		}
		else {
			if(i==4) {
				if(a!=2) {
					tot+=dfs(x-1, 1, i, len==3?3:(i==b?len+1:1), 0, line && i==g);
				}
			}
			else if(i==8) {
				if(a!=1) {
					tot+=dfs(x-1, 2, i, len==3?3:(i==b?len+1:1), 0, line && i==g);
				}
			}
			else {
				tot+=dfs(x-1, a, i, len==3?3:(i==b?len+1:1), 0, line && i==g);
			}
		}
	}
	if(!line && !first) {
		d[x][a][b][len]=tot;
	}
	return tot;
}
ll cal(ll n) {
	int top=0;
	for(; n; num[++top]=n%10, n/=10);
	return dfs(top, 0, 0, 0, 1, 1);
}
int main() {
	int c1=clock();
	freopen("4521.in","r",stdin);
	
	
	memset(d, -1, sizeof d);
	int T; scanf("%d",&T);
	while(T--)
	{
		ll L, R;
//		cin >> L >> R;
		scanf("%lld%lld",&L,&R);
//		cout << cal(R) - cal(L-1) << endl;
	}
	int c2=clock();
	printf("time %d\n",c2-c1);
	return 0;
}