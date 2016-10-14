//0/1-indexed Node
//0-indexed Edge
struct Edge{
	int pfr,pto;
	ll len;
}eg[M];
int nxt[M],head[N],egtot;
ll dis[N];
bool vis[N];
int spe[M],scnt;
int n,m,L,s,t;
void addEdge(int p1,int p2,ll len)
{
	eg[egtot]=(Edge){p1,p2,len};
	nxt[egtot]=head[p1];
	head[p1]=egtot++;
}
void dijkstra()
{
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;
	for(int i=0;i<=n;i++)
		vis[i]=0,dis[i]=INF;
	dis[s]=0;
	pq.push(mp(dis[s],s));
	while(!pq.empty())
	{
		pair<ll,int> p;
		do{
			p=pq.top();pq.pop();
		}while(!pq.empty() && vis[p.scd]);
		if(vis[p.scd]) break;
		vis[p.scd]=1;
		for(int i=head[p.scd];~i;i=nxt[i])
			if(dis[eg[i].pto]>dis[p.scd]+eg[i].len)
			{
				dis[eg[i].pto]=dis[p.scd]+eg[i].len;
				pq.push(mp(dis[eg[i].pto],eg[i].pto));
//				dbg(eg[i].pto);
//				dbg(dis[eg[i].pto]);
			}
	}
}
bool check1(ll lim)
{
	for(int i=1;i<=lim;i++)
		eg[spe[i]].len=eg[spe[i]^1].len=1;
	for(int i=lim+1;i<=scnt;i++)
		eg[spe[i]].len=eg[spe[i]^1].len=INF;
	dijkstra();
	return dis[t]<=L;
}
bool check2(int pos,ll lim)
{
	eg[spe[pos]].len=eg[spe[pos]^1].len=lim;
	dijkstra();
//	dbg(dis[t]);
	return dis[t]<=L;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&L,&s,&t);
	for(int i=0;i<n;i++) head[i]=-1;
	for(int i=1;i<=m;i++)
	{
		int p1,p2;
		ll len;
		scanf("%d%d%I64d",&p1,&p2,&len);
		if(len==0) spe[++scnt]=egtot;
		addEdge(p1,p2,len);
		addEdge(p2,p1,len);
	}
	for(int i=1;i<=scnt;i++)
		eg[spe[i]].len=eg[spe[i]^1].len=INF;
	dijkstra();
	if(dis[t]<L) failed("NO");
	
	for(int i=1;i<=scnt;i++)
		eg[spe[i]].len=eg[spe[i]^1].len=1;
	dijkstra();
	if(dis[t]>L) failed("NO");
	if(scnt==0)
	{
		dijkstra();
		if(dis[t]==L)
		{
			printf("YES\n");
			for(int i=0;i<egtot;i+=2)
				printf("%d %d %I64d\n",eg[i].pfr,eg[i].pto,eg[i].len);
			return 0;
		}
		else failed("NO");
	}
	ll l=0,r=scnt,mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check1(mid)) r=mid;
		else l=mid;
	}
	int setp=r;
	l=1,r=INF;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check2(setp,mid)) l=mid;
		else r=mid;
	}
	eg[spe[setp]].len=eg[spe[setp]^1].len=l;
	printf("YES\n");
	for(int i=0;i<egtot;i+=2)
		printf("%d %d %I64d\n",eg[i].pfr,eg[i].pto,eg[i].len);
}
