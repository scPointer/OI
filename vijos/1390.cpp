#include <cstdio>
#include <cstring>
#define MAXN 6//21
int f[MAXN][1<<MAXN];
int fst[MAXN][1<<MAXN];
int nxt[MAXN][1<<MAXN];
//int left[MAXN][1<<MAXN];
int map[MAXN];
int n,m,t;
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	while(t-->0)
	{
		memset(f,0,sizeof(f));
		memset(map,0,sizeof(map));
		for(int i=0;i<n;i++)
		{
			char s[MAXN+1];
			scanf("%s",s);
			for(int j=0;j<m;j++)
			{
				if(s[j]=='1') map[j]+=1<<i;
			}
		}
		int inf;
		for(int j=(1<<n)-1;j>=0;j--)
			nxt[0][j]=-1;
		for(int j=(1<<n)-1;j>=0;j--)
		{
			inf=(j^(j>>1)^(j>>2)^(j<<1)^(j<<2)^map[0])&((1<<n)-1);
			f[0][inf]++;
			if(fst[0][inf]==0) fst[0][inf]=j;
			else{nxt[0][j]=fst[0][inf];fst[0][inf]=j;}
			
//			printf("put %d in %d\n",j,(j^(j>>1)^(j>>2)^(j<<1)^(j<<2)^map[0])&((1<<n)-1));
		}
		for(int i=1;i<n;i++)
		{
			for(int j=(1<<n)-1;j>=0;j--)
				nxt[i][j]=-1;
			for(int j=(1<<n)-1;j>=0;j--)
			{
				inf=(j^(j>>1)^(j>>2)^(j<<1)^(j<<2)^map[i])&((1<<n)-1);
//				int lf=inf;
				
				f[i][lf]+=f[i-1][j];
				
				
			}
		}
		printf("%d\n",f[n-1][0]);
	}
	return 0;
}