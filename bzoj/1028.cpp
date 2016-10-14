#include <cstdio>
#define N 405
#define M 1005
int cds[N],a[N],left[N];
int ans[N],anscnt;
int n,m;
int check()
{
	for(int i=1;i<=n;i++){a[i]=cds[i]%3;left[i]=cds[i]-a[i];}
	for(int i=1;i<=n-2;i++)
		if(a[i]>0)
		{a[i+1]-=a[i];a[i+2]-=a[i];a[i]=0;}
		else if(a[i]<0)
		{
			while(a[i]<0 && left[i]>=3) a[i]+=3,left[i]-=3;
			if(a[i]<0) return 0;
			if(a[i]>0)
				{a[i+1]-=a[i];a[i+2]-=a[i];a[i]=0;}
		}
	while(a[n-1]<0 && left[n-1]>=0) a[n-1]+=3,left[n-1]-=3;
	while(a[n]<0 && left[n]>=0) a[n]+=3,left[n]-=3;
	return a[n-1]==0 && a[n]==0? 1:0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=3*m+1;i++){scanf("%d",&x);cds[x]++;}
	for(int i=1,ron;i<=n;i++)
	{
		ron=0;
		cds[i]++;
		for(int j=1;j<=n;j++)
			if(cds[j]>=2)
			{
				cds[j]-=2;
				ron=check();
				cds[j]+=2;
				if(ron) break;
			}
		cds[i]--;
		if(ron) ans[++anscnt]=i;
	}
	if(anscnt>0)
	{
		for(int i=1;i<=anscnt-1;i++)
			printf("%d ",ans[i]);
		printf("%d",ans[anscnt]);
	}
	else printf("NO");
	return 0;
}
