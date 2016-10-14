#include <cstdio>
bool vis[10];
int num[10];
int main()
{
	for(int i=123;i<=333;i++)
	{
		for(int e=1;e<=9;e++)
			vis[e]=0;
		int j=i*2;
		int k=i*3;
		if(vis[i/100]==0) vis[i/100]=1;
		else continue;
		if(vis[i/10%10]==0) vis[i/10%10]=1;
		else continue;
		if(vis[i%10]==0) vis[i%10]=1;
		else continue;
		if(vis[j/100]==0) vis[j/100]=1;
		else continue;
		if(vis[j/10%10]==0) vis[j/10%10]=1;
		else continue;
		if(vis[j%10]==0) vis[j%10]=1;
		else continue;
		if(vis[k/100]==0) vis[k/100]=1;
		else continue;
		if(vis[k/10%10]==0) vis[k/10%10]=1;
		else continue;
		if(vis[k%10]==0) vis[k%10]=1;
		else continue;
		printf("%d %d %d\n",i,j,k);
	}
	return 0;
}
