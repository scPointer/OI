#include <cstdio>
#define N 1005
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
struct Node{int u,d,l,r,v;}nd[N*N];
int ndcnt;
int n,m,q;
int temp;
inline void goright(int& p,int cnt){while(cnt--)p=nd[p].r;}
inline void goleft(int& p,int cnt){while(cnt--)p=nd[p].l;}
inline void goup(int& p,int cnt){while(cnt--)p=nd[p].u;}
inline void godown(int& p,int cnt){while(cnt--)p=nd[p].d;}
inline void excleft(int p1,int p2,int cnt)
{
	while(cnt--)
	{
		nd[nd[p1].l].r=p2;
		nd[nd[p2].l].r=p1;
		temp=nd[p1].l;
		nd[p1].l=nd[p2].l;
		nd[p2].l=temp;
		p1=nd[p1].d;
		p2=nd[p2].d;
	}
}
inline void excdown(int p1,int p2,int cnt)
{
	while(cnt--)
	{
		nd[nd[p1].d].u=p2;
		nd[nd[p2].d].u=p1;
		temp=nd[p1].d;
		nd[p1].d=nd[p2].d;
		nd[p2].d=temp;
		p1=nd[p1].r;
		p2=nd[p2].r;
	}
}
inline void excright(int p1,int p2,int cnt)
{
	while(cnt--)
	{
		nd[nd[p1].r].l=p2;
		nd[nd[p2].r].l=p1;
		temp=nd[p1].r;
		nd[p1].r=nd[p2].r;
		nd[p2].r=temp;
		p1=nd[p1].u;
		p2=nd[p2].u;
	}
}
inline void excup(int p1,int p2,int cnt)
{
	while(cnt--)
	{
		nd[nd[p1].u].d=p2;
		nd[nd[p2].u].d=p1;
		temp=nd[p1].u;
		nd[p1].u=nd[p2].u;
		nd[p2].u=temp;
		p1=nd[p1].l;
		p2=nd[p2].l;
	}
}
int main()
{
	n=RD();m=RD();q=RD();
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=m+1;j++)
		{
			int np=++ndcnt;
			if(j>0) nd[np].l=np-1;
			if(j<m+1) nd[np].r=np+1;
			if(i>0) nd[np].u=np-m-2;
			if(i<n+1) nd[np].d=np+m+2;
			if(i>0 && i<=n && j>0 && j<=m)
				nd[np].v=RD();
		}
	int qe[8];
	for(int i=1;i<=q;i++)
	{
		int ai,bi,ci,di,hi,wi;
		ai=RD();bi=RD();ci=RD();di=RD();hi=RD();wi=RD();
		int p1=1,p2=1;
		goright(p1,bi);godown(p1,ai);
		goright(p2,di);godown(p2,ci);
		qe[0]=p1;qe[1]=p2;
		godown(p1,hi-1);
		godown(p2,hi-1);
		qe[2]=p1;
		qe[3]=p2;
		goright(p1,wi-1);
		goright(p2,wi-1);
		qe[4]=p1;
		qe[5]=p2;
		goup(p1,hi-1);
		goup(p2,hi-1);
		qe[6]=p1;
		qe[7]=p2;
		excleft(qe[0],qe[1],hi);
		excdown(qe[2],qe[3],wi);
		excright(qe[4],qe[5],hi);
		excup(qe[6],qe[7],wi);
	}
	int phead=1,ptr;
	for(int i=1;i<=n;i++)
	{
		ptr=phead=nd[phead].d;
		for(int j=1;j<=m;j++)
		{
			ptr=nd[ptr].r;
			printf("%d ",nd[ptr].v);
		}
		printf("\n");
	}
}
