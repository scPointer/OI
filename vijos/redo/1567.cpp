#include <cstdio>
#define MAXN 30//200050
int sa[MAXN],h[MAXN],rank[MAXN];
int ar1[MAXN],ar2[MAXN];
int tub[MAXN];
int len,n;
int s[MAXN];
void getSuffixArray(int len)
{
	int *x=ar1,*y=ar2;
	int m=27;
	for(int i=0;i<len;i++)
		++tub[ x[i] = s[i]];
	for(int i=1;i<m;i++)
		tub[i]+=tub[i-1];
	for(int i=len-1;i>=0;i--)
		sa[--tub[x[i]]]=i;
	for(int k=1;k<len;k<<=1)
	{
		int p=0;
		for(int i=len-k;i<len;i++)
			y[p++]=i;
		for(int i=0;i<len;i++)
			if(sa[i]>=k) y[p++]=sa[i]-k;
		
		for(int i=0;i<m;i++)
			tub[i]=0;
		for(int i=0;i<len;i++)
			++tub[x[i]];
		for(int i=1;i<m;i++)
			tub[i]+=tub[i-1];
		for(int i=len-1;i>0;i--)
			sa[--tub[x[y[i]]]]=y[i];
		
		int *kk=x;x=y;y=kk;
		p=1;x[sa[0]]=0;
		for(int i=1;i<len;i++)
			x[sa[i]]= y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?  p-1:p++;
		if(p>=len) break;
		m=p;
	}
}
void getH(int n)
{
	for(int i=0;i<n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=0;i<n;i++)
	{
		if(k>0) k--;
		int j=sa[rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		h[rank[i]]=k;
	}
}
int main()
{
	scanf("%d",&n);
	char c;
	while(len<n)
	{
		c=getchar();
		printf("[%c]",c);
		if(c>='a' && c<='z')
			s[len++]=c-'a'+1;
	}
	s[len++]=0;
	getSuffixArray(len);
	getH(len);
	long long ans=0;
	for(int i=1;i<n;i++)
		ans+=n-sa[i]-h[i];
	printf("%I64d",ans);
	return 0;
}
