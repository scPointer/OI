#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100050
int n,m;
int prev[N*8],val[N*8];
inline int getint(int& re)
{
	static char chr;
	while((chr=getchar())<'0' || chr>'9');
	re=chr-'0';
	while((chr=getchar())>='0' && chr<='9')
		re=re*10+chr-'0';
	return re;
}
inline void updata(int p)
{
	val[p]=max(val[p*2]+prev[p*2],val[p*2+1]+prev[p*2+1]);
}
inline void pushdown(int p)
{
	prev[p*2]+=prev[p];
	prev[p*2+1]+=prev[p];
	val[p]+=prev[p];prev[p]=0;
}
void settree(int p,int l,int r)
{
	if(l==r)
	{
		getint(val[p]);
		return;
	}
	int mid=(l+r)>>1;
	settree(p*2,l,mid);
	settree(p*2+1,mid+1,r);
	updata(p);
}
void add(int p,int l,int r,int gl,int gr,int c)
{
	if(gl<=l && r<=gr)
	{
		if(l==r)
		{
			val[p]+=c+prev[p];
			prev[p]=0;
		}
		else
		{
			prev[p]+=c;
			pushdown(p);
		}
		return;
	}
	if(prev[p]) pushdown(p);
	int mid=(l+r)>>1;
	if(gl<=mid) add(p*2,l,mid,gl,gr,c);
	if(gr>mid) add(p*2+1,mid+1,r,gl,gr,c);
	updata(p);
}
int query(int p,int l,int r,int gl,int gr)
{
	if(gl<=l && r<=gr) return val[p]+prev[p];
	if(prev[p]) pushdown(p);
	int mid=(l+r)>>1;
	if(gr<=mid) return query(p*2,l,mid,gl,gr);
	else if(gl>mid) return query(p*2+1,mid+1,r,gl,gr);
	else return max(query(p*2,l,mid,gl,gr),query(p*2+1,mid+1,r,gl,gr));
	updata(p);
}
int main()
{
	getint(n);
	settree(1,1,n);
	getint(m);
	int k,l,r,c;
	for(int i=1;i<=m;i++)
	{
		getint(k);
		if(k==1){getint(l);getint(r);scanf("%d",&c);
			add(1,1,n,l,r,c);}
		else{getint(l);getint(r);
			printf("%d\n",query(1,1,n,l,r));}
	}
	return 0;
}
