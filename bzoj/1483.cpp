#include <cstdio>
#define N 100005
#define COLOR 1000005
#define Min(a,b) (a<b?a:b)
int head[COLOR],dset[COLOR],len[COLOR],sumlen;
int nxt[N];
int sc[N];
int n;
int find(int p){return dset[p]==p?p:dset[p]=find(dset[p]);}
inline void addNode(int pos,int color)
{
	nxt[pos]=head[color];
	head[color]=pos;
	len[color]++;
}
int merge(int rc1,int rc2)
{
	if(len[rc1]==0 || len[rc2]==0) return 0;
	int c1=dset[rc1],c2=dset[rc2];
	for(int i=head[c1];i;i=nxt[i])
	{
		if(sc[i]!=sc[i-1]) sumlen--;
		if(i!=n&& sc[i]!=sc[i+1]) sumlen--;
	}
	for(int i=head[c1];i;i=nxt[i])
		sc[i]=c2;
	for(int i=head[c1];i;i=nxt[i])
	{
		if(sc[i]!=sc[i-1]) sumlen++;
		if(i!=n && sc[i]!=sc[i+1]) sumlen++;
	}
	for(int i=head[c1];i;i=nxt[i])
		if(nxt[i]==0) return i;
	return 0;
}
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&sc[i]);
	sc[0]=sc[n+1]=-1;
	for(int i=1;i<=n;i++)
		addNode(i,sc[i]);
	for(int i=1;i<=n;i++)
		if(sc[i]!=sc[i-1]) sumlen++;
	for(int i=1;i<COLOR;i++) dset[i]=i;
	for(int i=1,tp,c1,c2,_temp;i<=m;i++)
	{
		scanf("%d",&tp);
		if(tp==2) {printf("%d\n",sumlen);continue;}
		else if(tp==3)
		{
			for(int i=1;i<=n;i++)printf("%d ",sc[i]); putchar('\n');
			for(int i=1;i<=n;i++) printf("%d ",find(i)); putchar('\n');
			continue;
		}
		scanf("%d%d",&c1,&c2);
		_temp=dset[c1];dset[c1]=dset[c2];dset[c2]=_temp;
		if(len[c1]>len[c2])
		{
			int last=merge(c2,c1);
			if(last==0)
				head[c2]=head[c1];
			else{
				nxt[last]=head[c1];
				head[c1]=0;
			}
//			dset[find(c2)]=find(c1);
		}
		else
		{
			int last=merge(c1,c2);
			if(last==0)
				continue;
			nxt[last]=head[c2];
			head[c2]=head[c1];
			head[c1]=0;
		}
		len[c2]+=len[c1];len[c1]=0;
	}
}