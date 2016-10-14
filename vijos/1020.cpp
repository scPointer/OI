#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 51
#define M 1025
int n,m,waste,sumcake;
int cake[N],cleft[N],man[M],summan[M];
int mid;
inline int RD()
{
	static char cr;
	static int res;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
bool check(int p,int ck)
{
	if(waste+summan[p]>sumcake) return false;
//	if(!waste) printf("p=%d ck=%d waste=%d\n",p,ck,waste);
	if(!p) return true;
	//for(int i=ck;i!=ck-1;i=i%n+1)
	for(int i=ck;i<=n;i++)
		if(cleft[i]>=man[p])
		{
			cleft[i]-=man[p];
			if(cleft[i]<man[1]) waste+=cleft[i];
			if(man[i]==man[i-1] && check(p-1,i)) return true;
			else if(check(p-1,1)) return true;
/*			if(cleft[i]<man[1])
			{
				waste+=cleft[i];
				if(check(p-1,1)) return true;
				waste-=cleft[i];
			}
			else
			{
				if(man[i]==man[i-1] && check(p-1,ck)) return true;
				else if(check(p-1,1)) return true;
			}
	*/
			if(cleft[i]<man[1]) waste-=cleft[i];
			cleft[i]+=man[p];
		}
	return false;
}
bool solve(int p)
{
//	printf("solve %d\n",p);
	for(int i=1;i<=n;i++) cleft[i]=cake[i];
	waste=0;
	return check(p,1);
}
int main()
{
//	freopen("p1020.out","w",stdout);
	n=RD();for(int i=1;i<=n;i++) sumcake+= cake[i]=RD();
	m=RD();for(int i=1;i<=m;i++) 	summan[i]= summan[i-1]+ (man[i]=RD());
	sort(cake+1,cake+1+n);
	sort(man+1,man+1+m);
	int l=1,r=m+1;
	while(l<r-1)
	{
//		printf("L %d R %d\n",l,r);
		mid=(l+r)>>1;
		if(solve(mid)) l=mid;
		else r=mid;
	}
	printf("%d",l);
	return 0;
}
