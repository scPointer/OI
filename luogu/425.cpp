#include <cstdio>
int main()
{
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	c-=a;d-=b;
	if(d<0)
	{
		--c;
		d+=60;
	}
	printf("%d %d",c,d);
	return 0;
}
