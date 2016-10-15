#include <cstdio>
inline int RC()
{
	char cr;
	while( (cr=getchar())!='O' && cr!='X');
	return cr=='O'?1:0;
}
void PR(int val)
{
	if(val==1) printf("O");
	else if(val==0) printf("X");
	else if(val==-1) printf("+");
}
int ss[1005][10];
int main()
{
	int n;scanf("%d",&n);
	bool flag=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=4;j++)
			ss[i][j]=RC();
		if(!flag && ss[i][1]==1 && ss[i][2]==1)
		{
			ss[i][1]=-1;ss[i][2]=-1;
			flag=1;
		}
		if(!flag && ss[i][3]==1 && ss[i][4]==1)
		{
			ss[i][3]=-1;ss[i][4]=-1;
			flag=1;
		}
	}
	if(!flag) printf("NO");
	else
	{
		printf("YES\n");
		for(int i=1;i<=n;i++)
		{
			PR(ss[i][1]);
			PR(ss[i][2]);
			printf("|");
			PR(ss[i][3]);
			PR(ss[i][4]);
			printf("\n");
		}
	}
}
	