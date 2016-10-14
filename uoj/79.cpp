#include <cstdio>
#include <algorithm>
using namespace std;
#define N 505*10
#define M 124751*2
#define db(s,p) printf("%s%d\n",s,p)
#define stop {int _st;_st++;}
int e[M],next[M],etot,head[N];
int match[N],dset[N],link[N],type[N];
int vis[N],cnt;
int q[N],qfront,qback;
int n,m;
inline int RD()
{
	static char cr;
	static int res;
	while((cr=getchar())<'0' || cr>'9');
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
void addedge(int p1,int p2)
{
	e[++etot]=p2;
	next[etot]=head[p1];
	head[p1]=etot;
	e[++etot]=p1;
	next[etot]=head[p2];
	head[p2]=etot;
}
int find(int p)
{
	return p==dset[p]?p:dset[p]=find(dset[p]);
}
int LCA(int p1,int p2)
{
	cnt++;
//	db("cnt",cnt);
	while(1)
	{
		if(p1==0 && p2==0)
			stop
//		db("p1=",p1);
//		db("p2=",p2);
		if(p1)
		{
			p1=find(p1);
			if(vis[p1]==cnt) return p1;
			else vis[p1]=cnt;
			p1=link[match[p1]];
		}
		swap(p1,p2);
	}
}
void hana(int p1,int p2,int rt)
{
	while(find(p1)!=rt)
	{
		dset[p1]=dset[p2]=rt;
		link[p1]=p2;
//		printf("LINK[%d]=%d\n",p1,p2);
		if(type[match[p1]]!=1){type[q[++qfront]=match[p1]]=1;;db("add",match[p1]);}
		p2=match[p1];p1=link[p2];
	}
}
int trymatch(int sp)
{
//	db("aaaaaaaaaaaaaaaaaaaaaaaa",sp);
	for(int i=1;i<=n;i++)
		dset[i]=i,link[i]=type[i]=0;
	q[qfront=qback=1]=sp;type[sp]=1;
	while(qback<=qfront)
	{
		int p=q[qback++];
//		db("p=",p);
		for(int i=head[p];i;i=next[i])
		{
			if(find(e[i])==find(p)) continue;
//			db("e[i]=",e[i]);
			if(!match[e[i]])
			{
				for(int p1=e[i],p2=p,temp;p2;p2=link[p1=temp])
				{
					temp=match[p2];
					match[p1]=p2;match[p2]=p1;
				}
//				db("getlink",sp);
//				db("linkto",match[sp]);
				return 1;
			}
			else if(type[e[i]]==0)
			{
				link[e[i]]=p;
//				printf("LINK[%d]=%d\n",e[i],p);
//				db("yssss",match[e[i]]);
				type[e[i]]=2;type[q[++qfront]=match[e[i]]]=1;
			}
			else if(type[e[i]]==1)
			{
				int rt=LCA(e[i],p);
//				printf("rt%d of %d %d\n",rt,e[i],p);
//				if(find(p)!=rt) link[p]=e[i];
//				if(find(e[i])!=rt) link[e[i]]=p;
				hana(p,e[i],rt);
				hana(e[i],p,rt);
			}
		}
	}
	return 0;
}
int main()
{
	freopen("p79.in","r",stdin);
	n=RD();m=RD();int ans=0;
	for(int i=1;i<=m;i++)
		addedge(RD(),RD());
	for(int i=1;i<=n;i++)
		if(!match[i]) ans+=trymatch(i);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d ",match[i]);
	return 0;
}
