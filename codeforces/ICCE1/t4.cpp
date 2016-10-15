#include <cstdio>
inline int RD()
{
	int res;
	char cr;
	while( (cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
int main()
{
	int n=RD();
	int hh=RD();
	int mm=RD();
	if(n==12)
	{
		if(hh==0) hh=1;
		if(hh>12)
		{
			while(hh>12)
				hh-=10;
		}
	}
	else
	{
		if(hh>23)
		{
			while(hh>23)
				hh-=10;
		}
	}
	if(mm>59)
	{
		while(mm>59)
			mm-=10;
	}
	if(hh<10) printf("0");
	printf("%d:",hh);
	if(mm<10) printf("0");
	printf("%d\n",mm);
}
