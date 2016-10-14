#include <cstdio>
#define INF 1000000000000ll
typedef long long ll;
int n;
int query(int x1,int y1,int x2,int y2)
{
	printf("? %d %d %d %d\n",x1,y1,x2,y2);
	fflush(stdout);
	int res;scanf("%d",&res);
	return res;
}
int check1(int sum)
{
	int l=1,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(query(mid,1,n,n)<sum) r=mid;
		else l=mid;
	}
	return l;
}
int check2(int sum)
{
	int l=0,r=n,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(query(1,1,mid,n)>=sum) r=mid;
		else l=mid;
	}
	return r;
}
int check3(int sum)
{
	int l=1,r=n+1,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(query(1,mid,n,n)<sum) r=mid;
		else l=mid;
	}
	return l;
}
int check4(int sum)
{
	int l=0,r=n,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(query(1,1,n,mid)>=sum) r=mid;
		else l=mid;
	}
	return r;
}
int main()
{
	scanf("%d",&n);
	fflush(stdout);
	int x[2][2],y[2][2];
	x[0][0]=check1(2);
	x[0][1]=check1(1);
	x[1][0]=check2(1);
	x[1][1]=check2(2);
	y[0][0]=check3(2);
	y[0][1]=check3(1);
	y[1][0]=check4(1);
	y[1][1]=check4(2);
	ll S=INF;
	int sets[4];
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				for(int l=0;l<2;l++)
				{
					if(x[0][i]>x[1][k]) continue;
					if(y[0][j]>y[1][l]) continue;
					if(x[0][i^1]>x[1][k^1]) continue;
					if(y[0][j^1]>y[1][l^1]) continue;
					if(query(x[0][i],y[0][j],x[1][k],y[1][l])==1)
					{
						if((ll)(x[1][k]-x[0][i]+1)*(y[1][l]-y[0][j]+1)<S)
						{
							S=(ll)(x[1][k]-x[0][i]+1)*(y[1][l]-y[0][j]+1);
							sets[0]=i;
							sets[1]=j;
							sets[2]=k;
							sets[3]=l;
						}
					}
				}
	if(S==INF)
	{
		printf("! %d %d %d %d %d %d %d %d",x[0][0],y[0][0],x[1][0],y[1][0],x[0][1],y[0][1],x[1][1],y[1][1]);
	}
	else
	{
		printf("! %d %d %d %d %d %d %d %d",x[0][sets[0]],y[0][sets[1]],x[1][sets[2]],y[1][sets[3]],x[0][sets[0]^1],y[0][sets[1]^1],x[1][sets[2]^1],y[1][sets[3]^1]);
	}
	return 0;
}
