#include <cstdio>
#include <cstring>
#define N 1005
char s[1005];
int p[N];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		fgets(s,N-5,stdin);
		while(s[0]=='\n')
			fgets(s,N-5,stdin);
		for(int j=strlen(s)-1;j>=0;j--)
			if(s[j]=='a' || s[j]=='e' || s[j]=='i' || s[j]=='o' || s[j]=='u' || s[j]=='y')
				cnt++;
		if(cnt!=p[i]){printf("NO\n");return 0;}
	}
	printf("YES\n");
	return 0;
}
