#include <cstdio>
#include <algorithm>
#define N 105
using namespace std;
int left2[N*N],cnt,num[N*N];
int a[5],ans;
int find(int p)
{
	int l,r,mid;
	l=1,r=cnt;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(left2[mid]>p) r=mid-1;
		else if(left2[mid]<p) l=mid+1;
		else if(left2[mid]==p && left2[mid+1]==p) l=mid+1;
		else return num[mid];
	}
	return 0;
}
int main()
{
	for(int i=0;i<5;i++) scanf("%d",&a[i]);
	for(int i=-50;i<=50;i++)
		for(int j=-50;j<=50;j++)
			if(i*j!=0)
				left2[++cnt]=a[0]*i*i*i+a[1]*j*j*j;
	sort(left2+1,left2+1+cnt);
	for(int i=1;i<=cnt;i++)
		if(left2[i]==left2[i-1])
			num[i]=num[i-1]+1;
		else num[i]=1;
		
	for(int i=-50;i<=50;i++)
		for(int j=-50;j<=50;j++)
			for(int k=-50;k<=50;k++)
				if(i*j*k!=0) ans+=find((a[2]*i*i*i+a[3]*j*j*j+a[4]*k*k*k)*(-1));
	printf("%d",ans);
	return 0;
}
