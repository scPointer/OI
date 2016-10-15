#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define ll long long
using namespace std;
int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int ans,dis[200005];
int n,tot,T,cnt=1;
int last[200005],pri[200005],q[200005];
bool mark[200005],inq[200005];
vector<int>q1,q2;
struct edge{
    int to,next,v,c;
}e[2000005];
void insert(int u,int v,int w,int c)
{
    e[++cnt]=(edge){v,last[u],w,c};last[u]=cnt;
    e[++cnt]=(edge){u,last[v],0,-c};last[v]=cnt;
}
bool spfa()
{
    for(int i=0;i<=T;i++)dis[i]=-inf;
    int head=0,tail=1;
    q[0]=T;dis[T]=0;
    while(head!=tail)
    {
        int now=q[head];head++;if(head==200000)head=0;
        inq[now]=0;
        for(int i=last[now];i;i=e[i].next)
            if(e[i^1].v&&dis[now]-e[i].c>dis[e[i].to])
            {
                dis[e[i].to]=dis[now]-e[i].c;
                if(!inq[e[i].to])
                {
                    q[tail++]=e[i].to;
                    if(tail==200000)tail=0;
                    inq[e[i].to]=1;
                }
            }
    }
    return dis[0]>0;
}
int v(int n,int x)
{
    ll t=x;while(x*t<=n)t*=x;
    return t;
}
void build()
{
    for(int i=1;i<=tot;i++)
    {
        int t=pri[i];
        if(t*2>n){ans+=t;continue;}
        if((ll)t*t<=n)
        {
            insert(0,i,1,0);
            ans+=v(n,t);
            q1.push_back(i);
        }
        else
        {
            insert(i,T,1,0);
            ans+=t;
            q2.push_back(i);
        }
    }
    for(int i=0;i<q1.size();i++)
        for(int j=0;j<q2.size();j++)
        {
            int a=pri[q1[i]],b=pri[q2[j]];
            if(a*b<=n)
            {
                int tmp=v(n/b,a)*b;
                if(tmp>v(n,a)+b)
				{
                    insert(q1[i],q2[j],1,tmp-(v(n,a)+b));
					printf("%d-%d at %d\n",pri[q1[i]],pri[q2[j]],cnt-1);
				}
            }
            else break;
        }
}
int dfs(int x,int f)
{
    mark[x]=1;
    if(x==T)return f;
    int w,used=0;
    for(int i=last[x];i;i=e[i].next)
        if(e[i].v&&dis[x]-e[i].c==dis[e[i].to]&&!mark[e[i].to])
        {
            w=dfs(e[i].to,min(e[i].v,f-used));
            e[i].v-=w;e[i^1].v+=w;
            ans+=e[i].c*w;used+=w;if(used==f)return f;
        }
    return used;
}
void zkw()
{
    while(spfa())
    {
        for(int i=0;i<=T;i++)mark[i]=0;
        mark[T]=1;
        while(mark[T])
            mark[T]=0,dfs(0,inf);
    }
}
int main()
{
    n=read();
    for(int i=2;i<=n;i++)
    {
        if(!mark[i])pri[++tot]=i;
        for(int j=1;pri[j]*i<=n&&j<=tot;j++)
        {
            mark[pri[j]*i]=1;
            if(i%pri[j]==0)break;
        }
    }
    T=n+1;
    build();
    zkw();
    printf("%d\n",ans+1);
	for(int i=418;i<=cnt;i+=2)
		if(e[i].v==0)
			printf("%d used\n",i);
    return 0;
}