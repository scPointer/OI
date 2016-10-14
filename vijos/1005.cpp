#include <cstdio>
#include <cstring>
#define MAXN 205
#define MAX(a,b) (a>b?a:b)
char qu[MAXN];
int l9[MAXN];
int sbt[MAXN][MAXN];//same bits
bool cmp1(int al,int ar,int bl,int br)
{
	if(qu[ar-1]==qu[br-1]-1)
	{
		while(al<=--ar&&bl<=--br)
			if(qu[ar-1]!=qu[br-1]) return 0;
		return 1;
	}
	else if(qu[ar-1]=='9'&&qu[br-1]='0')
}
int main()
{
	scanf("%s",qu);
	int len=strlen(qu);
	for(int i=0;i<=len-1;i++)
		if(qu[i]=='9') l9[i]=l9[i-1]+1;
//		else l9[i]=0;

	for(int i=1;i<=len;i++)
		for(int j=1;j<=len;j++)
			sbt[i][j]=-1;
	for(int i=1;i<=len-1;i++)
		for(int j=i+1;j<=len;j++)
		{
			int k=0;
			while(j+k<=len&&sbt[i][j]==-1&&qu[i+k-1]==qu[j+k-1]) k++;
			if(j+k>len) k--;
			if(sbt[i][j]>=0) continue;
			for(int l=0;l<=k;l++)
				sbt[i+l][j+l]=k-l+1;
		}
	
	for(int i=1;i<=len;i++)
	{
		for(int j=1;j<=i;j++)
		{
			int bits=i;
			for(int k=j-bits+1;k<=len;k+=bits)
			{
				if(k<=0)
				{
					if(l9[1]<bits) cmp1(1,k+bits-1,k+bits,k+bits*2-1);
			}
		}
	}
	return 0;
}
