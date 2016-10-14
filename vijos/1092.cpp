#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
bool used[21];
long long en[21];
int main()
{
	while(1)
	{
		memset(used,0,sizeof(used));
		long long n=0,m=0;
		cin>>n>>m;
	//	cout<<"\n"<<n<<' '<<m;
		en[0]=1;
		for(int i=1;i<=n;i++)
			en[i]=en[i-1]*i;
		for(int i=n-1;i>=1;i--)
		{
			long long a=(m-1)/en[i];
			if(a>0) m-=(a-1)*en[i];
			int num=0;
			if(a==0)
			{
				int t;
				for(t=1;used[t]==1;t++);
				used[t]=1;
				cout<<t<<' ';
			}
			else
				for(int j=1;j<=n;j++)
				{
					if(used[j]==0) num++;
					if(num==a)
					{
						used[j]=1;
						cout<<j<<' ';
						break;
					}
				}
		}
		for(int i=1;i<=n;i++)
			if(used[i]==0) cout<<i<<' ';
	//	for(int i=1;i<=n;i++)
	//		cout<<en[i]<<endl;
		cout<<endl;
	}
	return 0;
}
