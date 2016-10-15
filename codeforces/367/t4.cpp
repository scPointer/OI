#include <cstdio>
#define NDS 6500005
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
inline char getOrder()
{
	char cr;
	while( (cr=getchar())!='+' && cr!='-' && cr!='?');
	return cr;
}
int cnt[NDS],ls[NDS],rs[NDS],ndcnt;
int rot;
int insert(int v,int flo,int p,int cc)
{
	if(flo<0)
	{
		int np=++ndcnt;
		cnt[np]=cnt[p]+cc;
		return np;
	}
	int np=++ndcnt;
	cnt[np]=cnt[p]+cc;
	ls[np]=ls[p];rs[np]=rs[p];
	if((v>>flo)&1)
		rs[np]=insert(v,flo-1,rs[p],cc);
	else ls[np]=insert(v,flo-1,ls[p],cc);
	return np;
}
int query(int v,int flo,int p)
{
	if(flo<0) return 0;
	if((v>>flo)&1)
	{
		if(cnt[ls[p]]>0)
			return query(v,flo-1,ls[p])+(1<<flo);
		else
			return query(v,flo-1,rs[p]);
	}
	else
	{
		if(cnt[rs[p]]>0)
			return query(v,flo-1,rs[p])+(1<<flo);
		else
			return query(v,flo-1,ls[p]);
	}
}
int main()
{
	int q=RD();
	rot=insert(0,31,rot,1);
	while(q--)
	{
		char odr=getOrder();
		int val=RD();
		if(odr=='+')
			rot=insert(val,31,rot,1);
		else if(odr=='-')
			rot=insert(val,31,rot,-1);
		else
		{
			printf("%d\n",query(val,31,rot));
		}
	}
}
