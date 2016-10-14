#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100050
#define L 10000050
#define revhash(i) (h[i])
int l[L],r[L],c[L],T[N],tot;
int h[N],len;
int sc[N];
int n,q;
inline int rd(int& res)
{
	static char cr;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}

int hash()
{
	int res=0;
	memcpy(h,sc,sizeof(int)*(n+1));
	sort(h+1,h+1+n);
	for(int i=1;i<=n;i++)
		if(h[res]!=h[i]) h[++res]=h[i];
	return res;
}
int gethash(int key)
{
	static int l,r,mid;
	l=1;r=len+1;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(h[mid]<=key) l=mid;
		else r=mid;
	}
	return l;
}
int updata(int rt,int p,int nb)
{
	int newrt=++tot,ll=1,rr=len,mid;
	int setroot=newrt;
	c[newrt]=c[rt]+nb;
	while(ll<rr)
	{
		mid=(ll+rr)>>1;
		if(p<=mid)
		{
			r[newrt]=r[rt];
			l[newrt]=++tot;
			rt=l[rt];
			newrt=l[newrt];
			rr=mid;
		}
		else
		{
			l[newrt]=l[rt];
			r[newrt]=++tot;
			rt=r[rt];
			newrt=r[newrt];
			ll=mid+1;
		}
		c[newrt]=c[rt]+nb;
	}
	return setroot;
}
int kth(int lrt,int rrt,int k)
{
	int ll=1,rr=len,mid;
	while(ll<rr)
	{
		mid=(ll+rr)>>1;
		if(c[l[lrt]]-c[l[rrt]]<k)
		{
			k-=c[l[lrt]]-c[l[rrt]];
			lrt=r[lrt];rrt=r[rrt];
			ll=mid+1;
		}
		else
		{
			lrt=l[lrt];rrt=l[rrt];
			rr=mid;
		}
	}
	return revhash(ll);
}
int settree(int ll,int rr)
{
	int root=++tot;
	if(ll==rr) return root;
	l[root]=settree(ll,(ll+rr)>>1);
	r[root]=settree(((ll+rr)>>1)+1,rr);
	return root;
}
int main()
{
	rd(n);rd(q);
	for(int i=1;i<=n;i++) rd(sc[i]);
	len=hash();
	
	T[n+1]=settree(1,len);
	for(int i=n;i>=1;i--)
		T[i]=updata(T[i+1],gethash(sc[i]),1);
	int ql,qr,k;
	while(q--)
	{
		rd(ql);rd(qr);rd(k);
		printf("%d\n",kth(T[ql],T[qr+1],k));
	}
	return 0;
}
