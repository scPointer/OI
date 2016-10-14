#include <cstdio>
int n,cnt,f,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		f=i;
		while(f>0)
		{
			if(f%10==m) cnt++;
			f/=10;
		}
	}
	printf("%d",cnt);
	return 0;
}
