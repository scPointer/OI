#include <cstdio>
#include <algorithm>
#define N 50005
int cnt[N];
int sc[N];
int kot[N];
int thr;
struct Que{int l,r,id;}q[N];
bool cmp(Que a,Que b){return a.l/thr==b.l/thr? a.r<b.r: a.l<b.l;}
bool cmp2(Que a,Que b){return a.id<b.id;}
int gcd(int a,int b){return b==0? a: gcd(b,a%b);}
int main()
{
//	freopen("2038.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&sc[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	thr=233;
	std::sort(q+1,q+1+m,cmp);
	int p=1;
	for(int i=0;i<=n/thr;i++)
	{
		if(p<=m && q[p].l/thr==i)
		{
			int ans=0;
			for(int j=0;j<=n;j++) cnt[j]=0;
			for(int j=q[p].l;j<=q[p].r;j++)
				ans+=cnt[sc[j]]++;
			kot[q[p].id]=ans;
			while(++p<=m && q[p].l/thr==i)
			{
				for(int j=q[p-1].r+1;j<=q[p].r;j++)
					ans+= cnt[sc[j]]++;
				for(int j=q[p-1].l;j<=q[p].l-1;j++)
					ans-= --cnt[sc[j]];
				for(int j=q[p-1].l-1;j>=q[p].l;j--)
					ans+= cnt[sc[j]]++;
				kot[q[p].id]= ans;
			}
		}
	}
	std::sort(q+1,q+1+m,cmp2);
	for(int i=1,sum,gd;i<=m;i++)
	{
		sum=(long long)(q[i].r-q[i].l+1)*(q[i].r-q[i].l)/2;
		if(sum==0 || kot[i]==0)
			printf("0/1\n");
		else
		{
			gd=gcd(sum,kot[i]);
			printf("%d/%d\n",kot[i]/gd,sum/gd);
		}
	}
}