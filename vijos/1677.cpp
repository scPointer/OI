#include <cstdio>
#include <cstring>
#define MAXN 10//1000050
struct Node{
	int p;
	int next;
}nd[MAXN];
int head[MAXN],ndtop;//for Adjacency Table
int f[MAXN];//the array for KMP
int lt[MAXN],rt[MAXN];//[mean last,next]two-way chained list
int incl[MAXN];

char na[MAXN];
void addnode(int frt,int len)
{
	ndtop++;
	nd[ndtop].p=frt;
	nd[ndtop].next=head[len];
	head[len]=ndtop;
}
void kmp(char* s,int len)
{
	incl[0]=1;
	f[0]=-1;
	for(int i=1;i<len;i++)
	{
		int j=f[i];
		while(j>=0&&s[i]!=s[j]) j=f[j];
//		f[i+1]= s[j]==s[i]?j+1:0;
		if(j>=0&&s[j]==s[i])
		{
			f[i+1]=	j+1;
			addnode(i-j,j+1);
//			if(j>=1)
				incl[i-j]++;
		}
	}
}
int gotchainedlist(char *s,int len)
{
	for(int i=0;i<=len;i++)
		lt[i]=rt[i]=-1;
	int rightp=0,maxl=0;
	lt[0]=rt[0]=0;
	for(int i=1;i<len;i++)
		if(s[i]==s[0])
		{
			lt[i]=rightp;
			rt[rightp]=i;
//			incl[i]=1;
//			maxl=max(maxl,i-rightp);
			if(i-rightp>maxl) maxl=i-rightp;
			rightp=i;
		}
	rt[rightp]=rightp;
	return rightp;
}
bool delnodes(int nalen,int len,int thelast)
{
	bool access=1;
	for(int kp=head[len];nd[kp].p!=0;kp=nd[kp].next)
	{
		int p=nd[kp].p;
		if(incl[p]>0)
		{
			if(p==thelast) thelast=lt[p];
			
			int dist=rt[p]-lt[p];
			incl[p]--;
			if(incl[p]==0)
			{
				if(dist>len) access=0;
				lt[rt[p]]=lt[p];
				rt[lt[p]]=rt[p];
			}
		}
	}
	return access&&(thelast==nalen-len);
}
int main()
{
	scanf("%s",na);
	int len=strlen(na);
	int thelast=gotchainedlist(na,len);
	kmp(na,len);//algorithm KMP
	for(int i=1;i<=len;i++)
	{
		if(delnodes(len,i,thelast)==1)
		{
			printf("%d",i);
			break;
		}
	}
	return 0;
}
