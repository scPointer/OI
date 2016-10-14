#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 200050
#define lowbit(i) i&(-i)
struct node{
	int son[26];
	int v;
	int dad;
	int fail;
}nd[MAXN];
int non;//Trie和AC自动机
int ndprt[MAXN],ntop;//打印标记栈

struct Edge{int pto,next;}edge[MAXN];
int head[MAXN],etop;//边集数组

int odr[MAXN*2],timestamp;
int inp[MAXN],outp[MAXN];//DFS序相关

int nq[MAXN],fq[MAXN],qs[MAXN];//存储问题的邻接表

int bitree[MAXN];//树状数组

int answer[MAXN];
char source[MAXN];
int n,m,slen;
void setAho()
{
	int p=0;
	for(int i=0;i<slen;i++)
	{
		char c=source[i];
		if(c>='a' && c<='z')
		{
			if(nd[p].son[c-'a']==0)
			{
				++non;
				nd[non].v=c-'a';
				nd[non].dad=p;
				nd[p].son[c-'a']=non;
				p=non;
			}
			else p=nd[p].son[c-'a'];
		}
		else if(c=='P') ndprt[++ntop]=p;
		else p=nd[p].dad;
	}
}
void getFail()
{
//	nd[0].fail=0;
	queue<int> q;
	for(int i=0;i<26;i++)
		if(nd[0].son[i]!=0)
			q.push(nd[0].son[i]);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<26;i++)
			if(nd[u].son[i]!=0)
			{
				int r=nd[u].son[i];
				int t=nd[u].fail;
//				while(t && nd[t].v!=nd[r].v) t=nd[t].fail;[WRONG]
				while(t && !nd[t].son[i]) t=nd[t].fail;
				nd[r].fail= nd[t].son[i]? nd[t].son[i] : 0;
				q.push(r);
			}
	}
}
void addEdge(int p1,int p2)
{
	edge[++etop]=(Edge){p2,head[p1]};
	head[p1]=etop;
}
void getDFSOrder(int p)
{
	inp[p]=++timestamp;
	odr[timestamp]=p;
	for(int i=head[p];i;i=edge[i].next)
		getDFSOrder(edge[i].pto);
	outp[p]=++timestamp;
	odr[timestamp]=p;
}
void setFailTree()
{
	for(int i=1;i<=non;i++) addEdge(nd[i].fail,i);
	getDFSOrder(0);
}
void readinquestions()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		qs[i]=ndprt[p1];
		if(fq[ndprt[p2]]==0) fq[ndprt[p2]]=i;
		else{nq[i]=fq[ndprt[p2]];fq[ndprt[p2]]=i;}
	}
}
void add(int x,int v)
{
	for(;x<=timestamp;x+=lowbit(x))
		bitree[x]+=v;
}
int sum(int l,int r)
{
	int ret=0;
	for(;r>0;r-=lowbit(r))
		ret+=bitree[r];
	for(;l>0;l-=lowbit(l))
		ret-=bitree[l];
	return ret;
}
void solve()
{
	int p=0;
	add(inp[p],1);
	add(outp[p],-1);
	for(int i=0;i<slen;i++)
	{
		char c=source[i];
		if(c=='B') 
		{
			add(inp[p],-1);
//			add(outp[p],1);
			p=nd[p].dad;
		}
		else if(c>='a' && c<='z')
		{
			p=nd[p].son[c-'a'];
			add(inp[p],1);
//			add(outp[p],-1);
		}
		else
		{
			while(fq[p]!=0)
			{
				answer[fq[p]]=sum(inp[qs[fq[p]]]-1,outp[qs[fq[p]]]);
				fq[p]=nq[fq[p]];
			}
		}
	}
}
void printout()
{
	for(int i=1;i<=m;i++)
		printf("%d\n",answer[i]);
}
int main()
{
	fgets(source,MAXN,stdin);
	slen=strlen(source);
	setAho();
	getFail();
	setFailTree();
	readinquestions();
	solve();
	printout();
	return 0;
}
