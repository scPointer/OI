#include <cstdio>
#include <cstring>
#define N 300005
#define mo1 1000000007
#define mo2 1000000009
#define Max(a,b) (a>b?a:b)
typedef long long ll;
ll lh1[N],rh1[N];
ll lh2[N],rh2[N];
int ep1[N],ep2[N];
int len;
int lmax[N],rmax[N];
char s[N];
inline bool judge(ll s1[],ll s2[],int bas[],int l1,int l2,int l,int mo)
{
	
	ll p;
	if(l2>=l1) p=(s1[l1+l-1]-s1[l1-1])*bas[l2-l1]-(s2[l2+l-1]-s2[l2-1]);
	else p=(s2[l2+l-1]-s2[l2-1])*bas[l1-l2]-(s1[l1+l-1]-s1[l1-1]);
	return p%mo==0;
}
inline bool judge(int center,int pos)
{
	int range=pos-center;
	if(range<0) range=-range;
	if(center-range<1 || center+range>len) return 0;
	int l1=center-range,r1=center+range;
	int l2=len-r1+1,r2=len-l1+1;
	return judge(lh1,rh1,ep1,l1,l2,range+range+1,mo1) && judge(lh2,rh2,ep2,l1,l2,range+range+1,mo2);
}
void init()
{
	scanf("%s",s);
	len=strlen(s);
	for(int i=len-1;i>=0;i--)
		s[i<<1]=s[i];
	len=len*2-1;
	for(int i=len-1;i>=0;i--)
		if(i&1) s[i]=33;
		
	ep1[0]=ep2[0]=1;
	for(int i=1;i<=len;i++)
	{
		lh1[i]=(lh1[i-1]+(ll)s[i-1]*ep1[i-1])%mo1;
		lh2[i]=(lh2[i-1]+(ll)s[i-1]*ep2[i-1])%mo2;
		ep1[i]=(ll)ep1[i-1]*307%mo1;
		ep2[i]=(ll)ep2[i-1]*311%mo2;
	}
	for(int cnt=1,i=len;i>=1;i--,cnt++)
	{
		rh1[cnt]=(rh1[cnt-1]+(ll)s[i-1]*ep1[cnt-1])%mo1;
		rh2[cnt]=(rh2[cnt-1]+(ll)s[i-1]*ep2[cnt-1])%mo2;
	}
}
int main()
{
	init();
	int center=1;
	for(int i=1;i<=len;i++)
	{
		while(!judge(center,i)) center++;
		lmax[i]=i-center+1;
	}
	center=len;
	for(int i=len;i>=1;i--)
	{
		while(!judge(center,i)) center--;
		rmax[i]=center-i+1;
	}
	int ans=0;
	for(int i=1;i+2<=len;i+=2)
		ans=Max(ans,lmax[i]+rmax[i+2]);
	printf("%d",ans);
}
