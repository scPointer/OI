#include <cstdio>
#include <algorithm>
#define N 2000005
struct rela{int v,id;}re[N];
bool cmp(rela a,rela b){return a.v<b.v;}
bool cmp2(rela a,rela b){return a.id<b.id;}
bool tp[N];
int dset[N];
int find(int p){return dset[p]==p? p: dset[p]=find(dset[p]);}
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1,rdtp;i<=n;i++){
			scanf("%d%d%d",&re[i<<1].v,&re[(i<<1)-1].v,&rdtp);
			tp[i]= rdtp;
			re[i<<1].id=re[(i<<1)-1].id=i;
		}
		std::sort(re+1,re+1+n+n,cmp);
		int p=0,nowg=-1;
		for(int i=1;i<=n+n;i++)
			if(re[i].v==nowg) re[i].v=p;
			else{nowg=re[i].v;re[i].v=++p;}
		std::sort(re+1,re+1+n+n,cmp2);
		bool flag=1;
		for(int i=0;i<=p;i++) dset[i]=i;
		for(int i=1,f1,f2;i<=n;i++)
			if(tp[i])
			{
				f1=find(re[i<<1].v);f2=find(re[(i<<1)-1].v);
				if(f1!=f2) dset[f1]=f2;
			}
		for(int i=1,f1,f2;i<=n;i++)
			if(!tp[i])
			{
				f1=find(re[i<<1].v);f2=find(re[(i<<1)-1].v);
				if(f1==f2){flag=0;break;}
			}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
}