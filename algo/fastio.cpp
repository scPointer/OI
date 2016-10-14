namespace fastio
{
	#define BUF 100005
	char __s[BUF],*_ss,*_st;
	inline char gchar()
	{
		if(_ss==_st)
		{
			_ss=__s;
			_st=_ss+fread(__s,sizeof(char),BUF-5,stdin);
		}
		return *_ss++;
	}
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
	#undef BUF
}