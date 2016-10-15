#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

int magi[50][50];
int n;
int main()
{
	cin>>n;
	if(n==1)
	{
		cout<<1;
		return 0;
	}
	magi[1][(1+n)/2]=1;
	int hang=1;
	int lie=(1+n)/2;
	for(int k=2;k<=n*n;k++)
	{

		if((hang==1)&&(lie!=n))
		{
			hang=n;
			lie+=1;
			magi[hang][lie]=k;
			continue;
		}
		if((lie==n)&&(hang!=1))
		{
			lie=1;
			hang-=1;
			magi[hang][lie]=k;
			continue;
		}
		if(hang==1&&lie==n)
		{
			hang+=1;
			magi[hang][lie]=k;
			continue;
		}
		if(hang!=1)
		{
			if(lie!=n)
			{
				if(magi[hang-1][lie+1]==0)
				{
					hang-=1;
					lie+=1;
					magi[hang][lie]=k;
					continue;
				}
				else
				{
					hang+=1;
					magi[hang][lie]=k;
					continue;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<magi[i][j]<<" ";
		}
		cout<<endl;
	} 
}