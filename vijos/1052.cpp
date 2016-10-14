#include <iostream>
#include <algorithm>
#define MAXN 102
using namespace std;
double tr[MAXN][MAXN],ans[MAXN];
int n;
bool work()
{
	for(int i=1;i<=n;i++)
	{
		int st=i;
		while(st<=n&&tr[st][i]==0) st++;
		if(st>n) return false;
		if(st!=i)
			for(int j=1;j<=n+1;j++)
				swap(tr[st][j],tr[i][j]);
		for(int j=i+1;j<=n;j++)
			if(tr[j][i]!=0)
				for(int k=n+1;k>=i;k--)
					tr[j][k]-=tr[i][k]/tr[i][i]*tr[j][i];
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=i+1;j<=n;j++)
			tr[i][n+1]-=tr[i][j]*ans[j];
		ans[i]=tr[i][n+1]/tr[i][i];
	}
	return true;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			cin>>tr[i][j];
	if(work())
		for(int i=1;i<=n;i++)
		{
			printf("%d",(int)(ans[i]+0.0001));
			if(i!=n) printf(" ");
		}
	return 0;
}
