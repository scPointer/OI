#include <cstdio>
#include <iostream>
#include <cstring>
#define MAXN 400050
int sc[MAXN];

int sa[MAXN],js[MAXN],t[MAXN],t2[MAXN];
int height[MAXN],rank[MAXN];
int n;
void init()
{
	scanf("%d",&n);
	int p=0;
	while(p<n)
	{
		char c=getchar();
		if(c>='a'&&c<='z')
			sc[p++]=c-'a'+1;
		//"+1": To ensure no item is '0'
		//turn to Line.63
	}
}
void suffix_array(int m)
{
	int i,*x=t,*y=t2;
	for(i=0;i<m;i++) js[i]=0;
	for(i=0;i<n;i++)	js[x[i]=sc[i]]++;
	for(i=1;i<m;i++) js[i]+=js[i-1];
	for(i=n-1;i>=0;i--) sa[--js[x[i]]]=i;
	for(int k=1;k<n;k<<=1)
	{
		int p=0;
		for(i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++)
			if(sa[i]>=k) y[p++]=sa[i]-k;
		
		for(i=0;i<m;i++) js[i]=0;
		for(i=0;i<n;i++) js[x[i]]++;
		for(i=1;i<m;i++) js[i]+=js[i-1];
		for(i=n-1;i>=0;i--) sa[--js[x[y[i]]]]=y[i];
		
		int *kk=x;x=y;y=kk;
		p=1;x[sa[0]]=0;
		
		for(i=1;i<n;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
		if(p>=n) break;
		m=p;
	}
}
void got_height()
{
	for(int i=0;i<n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=0;i<n;i++)
    {
        if(k>0) k--;
        int j=sa[rank[i]-1];
		//only the value of rank[n] is 0, because the last suffix is a single '0'
		//so rank[i]>=1 -> rank[i]-1>=0
        while(sc[i+k]==sc[j+k]) k++;
		//because no item in sc-array is 0,  sc[i]||sc[j] != 0
		//so k will not go infinity
        height[rank[i]]=k;
    }
}
int main()
{
	init();
	n++;
	//add in the last char '0' 
	suffix_array(28);
	//sa[n] is the last '0'
	got_height();
	//rank[0] is the last '0'
	long long ans=0;
    for(int i=1;i<n;i++)
	//height[n] has not be calculate(the last '0') [turn to the function "got_height"] 
        ans+=n-sa[i]-height[i];
    std::cout<<ans;
    return 0;
}
