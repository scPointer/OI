#include <cstdio>
#include <ctime>
#define BUF 100005
char __s[BUF],*_ss,*_st;
inline char gchar()
{
	if(_ss==_st)
	{
		_ss=__s;//s="12345" _ss->s[0]
		_st=_ss+fread(__s,sizeof(char),BUF-5,stdin);//-st->s[strlen(s)-1]
		//memset(a,0,sizeof(a));
		//
	}
	return *_ss++;//return *_ss,_ss++
}//getchar()
inline int RD()
{
	int res;
	char cr;
	while( (cr=gchar())<'0' || cr>'9');
	res=cr-'0';
	while( (cr=gchar())>='0' && cr<='9')
		res=(res<<1)+(res<<3)+cr-'0';
	return res;
}
int main()
{
	freopen("x.in","r",stdin);
	int c1=clock();
	int n=RD();
	for(int i=1,p;i<=n;i++)
		p=RD();
	printf("%d\n",clock()-c1);
}