#include <cstdio>
int exps[8];
int num[5],pn[5];
int symb,nnum;
bool dfs(int haveput)
{
	if(haveput<7)
	{
		for(int i=1;i<=4;i++)
		{
			if(pn[i]!=0) continue;
			exps[haveput+1]=i;
			nnum++;
			pn[i]=1;
			if(dfs(haveput+1)==1)
				return 1;
			pn[i]=0;
			nnum--;
//			exps[haveput+1]=0;
		}
		if(symb<nnum-1)
		{
			for(int i=-1;i>=-4;i--)
			{
				exps[haveput+1]=i;
				symb++;
				if(dfs(haveput+1)==1)
					return 1;
				symb--;
//				exps[haveput+1]=0;
			}
		}
		return 0;
	}
	int st[5],top=0;
//	bool flag=0;
	for(int i=1;i<=7;i++)
	{
		if(exps[i]>0) st[++top]=num[exps[i]];
		else
		{
			switch(exps[i])
			{
				case -1:st[top-1]+=st[top];break;
				case -2:st[top-1]-=st[top];break;
				case -3:st[top-1]*=st[top];break;
				case -4:
					if(st[top]==0||st[top-1]%st[top]!=0) 
//						flag=1;
						return 0;
					else st[top-1]/=st[top];
					break;
			}
			top--;
//			if(flag==1) return 0;
		}
	}
	if(st[1]==24) return 1;
	else return 0;
}
int main()
{
	char s[5][3];
	for(int i=1;i<=4;i++)
		scanf("%s",s[i]);
	for(int i=1;i<=4;i++)
	{
		if(s[i][1]=='0') num[i]=10;
		else if(s[i][0]<='9'&&s[i][0]>='1') num[i]=s[i][0]-'0';
		else if(s[i][0]=='A') num[i]=1;
		else if(s[i][0]=='J') num[i]=11;
		else if(s[i][0]=='Q') num[i]=12;
		else if(s[i][0]=='K') num[i]=13;
	}
//	for(int i=1;i<=4;i++)
//		printf("%3d",num[i]);
	symb=nnum=0;
	if(dfs(0)==1)
		printf("1");
	else printf("0");
	return 0;
}
