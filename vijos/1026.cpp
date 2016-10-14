#include <cstdio>
#include <cstring>
#define MAXSITUATION 1025
#define MAXM 101
struct edge{
	int pto;
	int next;
}ed[MAXM*MAXSITUATION];
int head[MAXSITUATION],edtop;
int n,m;
int queue[MAXSITUATION];
int inqueue[MAXSITUATION];
int times[MAXSITUATION];
int TopologicalSort()
{
	int start,end;
	bool flag=1;
	start=end=1;
	times[1]=0;
	inqueue[0]=1;
	queue[1]=0;
	while(/*end<=(1<<n)-1&&*/(flag==1||times[end]!=0))
	{
		flag=0;
		int p=head[queue[end]];
		while(ed[p].pto!=-1)
		{
			if(inqueue[ed[p].pto]==0)
			{
				flag=1;
				inqueue[ed[p].pto]=1;
				queue[++start]=ed[p].pto;
				times[start]=times[end]+1;
				if(queue[start]==(1<<n)-1) return times[start];
			}
			p=ed[p].next;
		}
		end++;
	}
	return -1;
}
void ReadEdge(int x,int y)
{
	if(x==y) return;
	edtop++;
	ed[edtop].pto=y;
	ed[edtop].next=head[x];
	head[x]=edtop;
}
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	ed[0].pto=-1;//!!!!!!!!!!!
	for(int i=1;i<=m;i++)
	{
		int cure=0,sick=(1<<n)-1;
		int k;
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&k);
			if(k==1)
				cure|=1<<(j-1);
			else if(k==-1)
				sick-=1<<(j-1);
		}
		for(int i=0;i<=(1<<n)-1;i++)
		{
			int stt1=i;//situation
			int stt2=(stt1|cure)&sick;
			ReadEdge(stt1,stt2);
		}
	}
	int ans=TopologicalSort();
	if(ans>0) printf("%d\n",ans);
	else printf("The patient will be dead.\n");
	return 0;
}
