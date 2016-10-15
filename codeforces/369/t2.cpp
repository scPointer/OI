#include <cstdio>
#include <iostream>
typedef long long ll;
ll mp[505][505];
int px,py;
ll sumx[505],sumy[505],sumd[5];
int main()
{
	int n;scanf("%d",&n);
	if(n==1)
	{
		std::cout<<"1";
		return 0;
	}
	for(int i=1,p;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&p);
			if(p==0)
			{
				px=i;py=j;
				continue;
			}
			mp[i][j]=p;
			sumx[i]+=p;
			sumy[j]+=p;
			if(i==j) sumd[1]+=p;
			if(i+j==n+1) sumd[2]+=p;
			
		}
	bool impsb=0;
	ll res= px==1? sumx[2]:sumx[1];
	for(int i=1;i<=n;i++)
	{
		if(px!=i)
		{
			if(sumx[i]!=res) impsb=1;
		}
		if(py!=i)
		{
			if(sumy[i]!=res) impsb=1;
		}
	}
	if(px!=py)
	{
		if(sumd[1]!=res) impsb=1;
	}
	if(px+py!=n+1)
	{
		if(sumd[2]!=res) impsb=1;
	}
	if(impsb)
	{
		std::cout<<"-1";
		return 0;
	}
	ll ans=res-sumx[px];
	if(ans<=0)
	{
		std::cout<<"-1";
		return 0;
	}
	if(res-sumy[py]!=ans) impsb=1;
	if(px==py && res-sumd[1]!=ans) impsb=1;
	if(px+py==n+1 && res-sumd[2]!=ans) impsb=1;
	if(impsb)
		std::cout<<"-1";
	else std::cout<<ans;
}