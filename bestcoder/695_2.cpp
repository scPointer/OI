#include <cstdio>
#include <cstring>
#define LEN 200005
char sc[LEN],trs[LEN];
int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		fgets(sc,LEN,stdin);
		while(sc[0]<32) fgets(sc,LEN,stdin);
		
		int sumlen=strlen(sc)-1;
		int len; scanf("%d",&len);
		int gro=(sumlen-1)/len+1;
		int cnt=0;
		for(int j=0;j<len;j++)
			for(int k=0;k<gro;k++)
				if(k*len+j<sumlen)
					trs[k*len+j]=sc[cnt++];
		trs[sumlen]='\0';
		printf("Case #%d:\n%s\n",i,trs);
	}
}