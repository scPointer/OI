#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#define ll long long
#define N 402020
#define pa pair<int,int>
using namespace std;
int sc()
{
    int i=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')i=i*10+c-'0',c=getchar();
    return i*f;
}
struct W{int l,r,p;}a[N];
int n,m,tot,fa[N][19],ans[N];
set<pa>st;
bool cmp(W a,W b)
{
    return a.l<b.l;
}
void solve(int x)
{
    int p=a[x].p,L=a[x].l+m;
    for(int i=18;i>=0;i--)
        if(fa[x][i])
            if(a[fa[x][i]].r<L)
                x=fa[x][i],ans[p]+=(1<<i);
}
int main()
{
	freopen("4444.in","r",stdin);
    n=sc(),m=sc();
    for(int i=1;i<=n;i++)
    {
        a[++tot].l=sc(),a[tot].r=sc(),a[tot].p=i;
        if(a[tot].r<a[tot].l)a[tot].r+=m;
        ++tot;
        a[tot].l=a[tot-1].l+m;
        a[tot].r=a[tot-1].r+m;
    }
    sort(a+1,a+tot+1,cmp);  
    st.insert(make_pair(a[tot].l,tot));
    for(int i=tot-1;i;i--)
    {
        fa[i][0]=(--st.upper_bound(make_pair(a[i].r,0x7FFFFFFF)))->second;
        st.insert(make_pair(a[i].l,i));
    }
    for(int i=1;i<=18;i++)
        for(int j=tot;j;j--)
            fa[j][i]=fa[fa[j][i-1]][i-1];
    for(int i=1;i<=tot;i++)
        if(a[i].p)
            solve(i);
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]+2);
    return 0;
}