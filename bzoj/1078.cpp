#include <cstdio>
#define N 205
#define Swap(a,b) {int _temp=a;a=b;b=_temp;}
int ans[N];
int ls[N],rs[N],fa[N];
int rt;
void remove(int p)
{
	if(p==rt){rt=ls[p];return;}
	ls[fa[p]]=ls[p]; fa[ls[p]]=fa[p];
	for(p=fa[p];p!=rt;p=fa[p])
		Swap(ls[p],rs[p])
	Swap(ls[p],rs[p]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d",&p);
		if(p<100)
			ls[p]=i,fa[i]=p;
		else
			rs[p-100]=i,fa[i]=p-100;
	}
	for(int i=n,p;i>=0;i--)
	{
		for(p=rt;rs[p]!=0;p=ls[p]);
		if(ls[p]!=0 && ls[ls[p]]==0)
			remove(ans[i]=ls[p]);
		else remove(ans[i]=p);
	}
	for(int i=0;i<=n;i++) printf("%d ",ans[i]);
}