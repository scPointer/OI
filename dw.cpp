#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
#define N 10050
inline int rd32(){return (rand()<<16)+rand();}
int a[N],cnt,arange,ERR;
int mo[]={0,1000000,5000000,10000000,50000000,100000000},monum=5;
int find(int p)
{
	int l,r,mid;
	l=1,r=cnt;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(a[mid]>p) r=mid-1;
		else if(a[mid]<p) l=mid+1;
		else 
		{
			if(a[mid]==a[mid-1] || a[mid]==a[mid+1]) ERR++;
			return p;
		}
	}
	return 0;
}
int main()
{
	srand(time(NULL));
	for(int f=1;f<=monum;f++)
	{
	
	arange=0;ERR=0;
	int T=100;
	for(int ii=1;ii<=T;ii++)
	{
		cnt=0;
		for(int i=1;i<=10000;i++)
			a[++cnt]=rd32()%mo[f];
		sort(a+1,a+1+cnt);
		int samenum=0;
		for(int i=1;i<=cnt;i++)
			if(a[i]==a[i-1]) samenum++;
//		printf("test %d: samenum= %d\n",T,samenum);
		for(int i=1;i<=1000000;i++)
			find(rd32()%mo[f]);
		arange+=samenum;
	}
	printf("MO=%d same%f ERR%f\n",mo[f],(double)arange/T,(double)ERR/T);
		
	}
	return 0;
}
