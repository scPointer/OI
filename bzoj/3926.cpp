#include <cstdio>
#include <cstring>
#include <iostream>
#define NDS 4000005
#define N 100005
struct Node{
	int val;
	Node* fa;
	Node* next[11];
}nodes[NDS],*root,*last;
int ndcnt;
inline void initNode(){root=last=&nodes[ndcnt=1];}
inline Node* newNode(){nodes[++ndcnt].fa=NULL;return &nodes[ndcnt];}
inline void cpynext(Node *p,Node *q){for(int i=0;i<=10;i++) p->next[i]=q->next[i];}
Node* addtail(Node* last,int x)
{
	Node *p=last,*np=newNode();np->val=p->val+1;
	while(p && !p->next[x])
		p->next[x]=np,p=p->fa;
	if(!p) np->fa=root;
	else
	{
		Node *q=p->next[x];
		if(q->val == p->val+1) np->fa=q;
		else
		{
			Node *nq=newNode();nq->val=p->val+1;
			cpynext(nq,q);
			nq->fa=q->fa;
			q->fa=np->fa=nq;
			while(p && p->next[x]==q)
				p->next[x]=nq,p=p->fa;
		}
	}
	return np;
}
int n,alpha;
int color[N];
int eg[N*2],nxt[N*2],head[N],deg[N],egcnt;
int vis[N],viscnt;
inline void addedge(int p1,int p2)
{
	eg[++egcnt]=p2;
	nxt[egcnt]=head[p1];
	head[p1]=egcnt;
}
void solve(Node* p,int i)
{
	vis[i]=viscnt;
//	printf("add%d\n",color[i]);
	Node* now=addtail(p,color[i]);
	for(int e=head[i];e;e=nxt[e])
		if(vis[eg[e]]!=viscnt)
			solve(now,eg[e]);
}
int main()
{
	initNode();
	scanf("%d%d",&n,&alpha);
	for(int i=1;i<=n;i++) scanf("%d",&color[i]);
	for(int i=1,p1,p2;i<=n-1;i++)
	{
		scanf("%d%d",&p1,&p2);
		deg[p1]++;deg[p2]++;
		addedge(p1,p2);addedge(p2,p1);
	}
	for(int i=1;i<=n;i++)
		if(deg[i]==1)
			++viscnt,solve(root,i);
	long long ans=0;
	for(int i=2;i<=ndcnt;i++)
	{
		ans+=nodes[i].val - nodes[i].fa ->val;
//		printf("[%d] val%d fa%d\n",i,nodes[i].val,nodes[i].fa->val);
	}
	std::cout<<ans;
	return 0;
}
