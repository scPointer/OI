#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef double lf;
#define pb push_back
#define SZ(x) ((int)(x).size())
inline int ri() {
	int x=0, f=1, c=getchar();
	for(; c<48||c>57; f=c=='-'?-1:f, c=getchar());
	for(; c>47&&c<58; x=x*10+c-48, c=getchar());
	return x*f;
}
using namespace std;
struct dat {
	int c, p;
};
vector<vector<dat> > a;
const int N=55;
int n, m, w[N], t[N];
lf ans;
void dfs(int x, lf p) {
	if(x==n) {
		for(int i=0; i<n; ++i) {
			t[i]=w[i];
		}
		sort(t, t+n);
		int cnt=m, sum=0;
		for(int i=n-1; i>=0 && cnt; --i, --cnt) {
			sum+=t[i];
		}
		ans+=p*sum;
		return;
	}
	for(int i=0; i<SZ(a[x]); ++i) {
		w[x]=a[x][i].c;
		dfs(x+1, a[x][i].p*p/10000);
	}
}
lf work() {
	ans=0;
	dfs(0, 1);
	return ans;
}
int main() {
	freopen("p0000.in","r",stdin);
	n=ri(), m=ri();
	for(int i=0; i<n; ++i) {
		int k=ri();
		vector<dat> b;
		for(int j=0; j<k; ++j) {
			dat t;
			t.c=ri();
			t.p=ri();
			b.pb(t);
		}
		a.pb(b);
	}
	printf("%.10f\n", work());
	return 0;
}
