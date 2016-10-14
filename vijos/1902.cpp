#include <cstdio>
#include <cstring>
char s[1010];
int count[9];
const int need[9]={-1,2,3,1,1,1,2,1,1};
int main()
{
	int t;
	scanf("%d",&t);
	fgets(s,1005,stdin);
	for(int aa=1;aa<=t;aa++)
	{
		memset(count,0,sizeof(count));
		fgets(s,1005,stdin);
//		while(s[0]=='\n')
//			fgets(s,1005,stdin);
		s[strlen(s)-1]='\0';
		int len=strlen(s);
//		printf("%d\n",strlen(s));
		for(int i=0;i<len;i++)
		{
			switch(s[i])
			{
				case 'g':count[1]++;break;
				case 'o':count[2]++;break;
				case 'd':count[3]++;break;
				case 'm':count[4]++;break;
				case 'r': count[5]++;break;
				case 'n':count [6]++;break;
				case 'i':count[7]++;break;
				case ' ':count[8]++;break;
			}
		}
		int min=1001;
		for(int j=1;j<=8;j++)
			if(count[j]/need[j]<min)
				min=count[j]/need[j];
		printf("Case #%d: %d\n",aa,min);
	}
	return 0;
}
