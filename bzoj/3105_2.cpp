    #include <cstdio>  
    #include <cstring>  
    #include <climits>  
    #include <algorithm>  
    using namespace std;  
       
    #define N 110  
    int n;  
    int a[N], w[N], ins[30], sav[N], top;  
       
    int main() {  
		freopen("3105.in","r",stdin);
        scanf("%d", &n);  
           
        register int i, j, k;  
        for(i = 1; i <= n; ++i)  
            scanf("%d", &a[i]);  
        sort(a + 1, a + n + 1);  
           
        long long tot = 0;  
        for(i = 1; i <= n; ++i)  
            tot += (w[i] = a[i]);  
           
        long long ans = 0;  
        for(i = n; i >= 1; --i) {  
            for(j = 29; j >= 0; --j) {  
                if ((a[i] >> j) & 1) {  
                    if (!ins[j]) {  
                        ins[j] = i;  
                        for(k = 1; k <= top; ++k)  
                            if ((a[sav[k]] >> j) & 1)  
                                a[sav[k]] ^= a[i];  
                        sav[++top] = i;  
                        break;  
                    }  
                    else  
                        a[i] ^= a[ins[j]];  
                }  
            }  
            if (a[i])  
                ans += w[i];  
        }  
           
        printf("%lld", tot - ans);  
           
        return 0;  
    }  