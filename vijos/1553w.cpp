#include <cstdio>
#include <cstring>
#define MAXN 10001
#define min(a,b) (a<b?a:b)
struct M{
	int edge[MAXN];
	int dis[MAXN];
	int etop;
	int sons[MAXN];
	int dad;
	int deep;
	bool belong;
}pot[MAXN];
int n,s,maxl,maxi,x,y,dt;
int t1,t2,dt1,dt2;
int ans;
int vis[MAXN],indt[MAXN];
int map[MAXN][MAXN];
int left[MAXN],right[MAXN],lenl[MAXN],lenr[MAXN];
void find_core()
{
	bool flag=0;
	if(t1==t2)
	{
		ans=dt/2;
		if(s==0||(left[0]==0&&right[0]==0)){printf("%d",ans);return;}
		int lp=1,rp=1;
		lenl[1]=map[t1][left[1]];
		lenr[1]=map[t2][right[1]];
		for(int i=2;i<=left[0];i++)
			lenl[i]=lenl[i-1]+map[left[i-1]][left[i]];
		for(int i=2;i<=right[0];i++)
			lenr[i]=lenr[i-1]+map[right[i-1]][right[i]];
		if(lenl[left[0]]+lenr[right[0]]<=s){printf("%d",(dt/2-min(lenl[left[0]],lenr[right[0]]))/2);return;}
/*		printf("\n");
		for(int i=1;i<=left[0];i++)
			printf("%3d<l>",lenl[i]);
		printf("\n");
		for(int i=1;i<=right[0];i++)
			printf("%3d<r>",lenr[i]);
		printf("\n");
		*/
		while(lenl[lp]+lenr[rp]<=s)
		{
			flag=1;
			if(lenl[lp]>=lenr[rp]) 
			{
				if(lenr[rp+1]!=0&&lenl[lp]+lenr[rp+1]<=s) rp++;
				else break;
			}
			else if(lenl[lp]<=lenr[rp])
			{
				if(lenl[lp+1]!=0&&lenr[rp]+lenl[lp+1]<=s) lp++;
				else break;
			}
		}
		if(flag==0){printf("%d",ans/2);return;}
		printf("%d",(dt/2-min(lenl[lp],lenr[rp]))/2);return;
	}
	else
	{
		ans=(dt/2+min(dt1,dt2));
		int lp=1,rp=1;
		lenl[1]=dt1;
		lenr[1]=dt2;
		for(int i=2;i<=left[0];i++)
			lenl[i]=lenl[i-1]+map[left[i-1]][left[i]];
		for(int i=2;i<=right[0];i++)
			lenr[i]=lenr[i-1]+map[right[i-1]][right[i]];
		if(lenl[left[0]]+lenr[right[0]]<=s){printf("%d",(dt/2-min(lenl[left[0]],lenr[right[0]]))/2);return;}
/*		printf("\n");
		for(int i=1;i<=left[0];i++)
			printf("%3d<l>",lenl[i]);
		printf("\n");
		for(int i=1;i<=right[0];i++)
			printf("%3d<r>",lenr[i]);
		printf("\n");
		*/
		while(lenl[lp]+lenr[rp]<=s)
		{
			flag=1;
			if(lenl[lp]>=lenr[rp]) 
			{
				if(lenr[rp+1]!=0&&lenl[lp]+lenr[rp+1]<=s) rp++;
				else break;
			}
			else if(lenl[lp]<=lenr[rp])
			{
				if(lenl[lp+1]!=0&&lenr[rp]+lenl[lp+1]<=s) lp++;
				else break;
			}
		}
		if(flag==0){printf("%d",ans/2);return;}
		printf("%d",(dt/2-min(lenl[lp],lenr[rp]))/2);return;
	}
}
bool find_same()
{
//	printf("t1:%dt2:%d\n",t1,t2);
	if(t1==t2&&pot[t1].sons[0]<=2)
	{
		int k1=pot[t1].sons[1];
		int k2=pot[t1].sons[2];
		left[++left[0]]=pot[t1].sons[1];
		right[++right[0]]=pot[t1].sons[2];
		while(pot[k1].sons[0]==1)
		{
			left[++left[0]]=pot[k1].sons[1];
			k1=pot[k1].sons[1];
		}
		while(pot[k2].sons[0]==1)
		{
			right[++right[0]]=pot[k2].sons[1];
			k2=pot[k2].sons[1];
		}
	}
	else if(t1==t2)
	{
		pot[t1].sons[0]=0;
		printf("%d",dt/4);
		return 1;
	}
	else if(t1!=t2)
	{
		int k1=t1;
		int k2=t2;
		left[++left[0]]=t1;
		right[++right[0]]=t2;
		while(pot[k1].sons[0]==1)
		{
			left[++left[0]]=pot[k1].sons[1];
			k1=pot[k1].sons[1];
		}
		while(pot[k2].sons[0]==1)
		{
			right[++right[0]]=pot[k2].sons[1];
			k2=pot[k2].sons[1];
		}
	}
	if(t1==t2) printf("%d",t1);
/*	printf("\nleft:");
	for(int i=1;i<=left[0];i++)
		printf("%3d",left[i]);
	printf("\nright:");
	for(int i=1;i<=right[0];i++)
		printf("%3d",right[i]);
	*/
}
void cut_tree()
{
	if(t1==t2)
	{
		for(int i=1;i<=n;i++)
		{
			if(pot[i].deep==dt/2)
			{
				indt[i]=1;
				while(indt[pot[i].dad]==0&&pot[i].dad!=t1)
				{
					i=pot[i].dad;
					indt[i]=1;
				}
			}
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			if((pot[i].deep==dt/2-dt1&&pot[i].belong==0)||(pot[i].deep==dt/2-dt2&&pot[i].belong==1))
			{
				indt[i]=1;
				int j=i;
				while(pot[j].dad!=0&&indt[pot[j].dad]==0)
				{
					j=pot[j].dad;
					indt[j]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=pot[i].etop;j++)
			if(indt[pot[i].edge[j]]==0)
			{
				for(int k=j;k<=pot[i].etop-1;k++)
				{
					pot[i].edge[k]=pot[i].edge[k+1];
					pot[i].dis[k]=pot[i].dis[k+1];
				}
				pot[i].etop--;j--;
			}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=pot[i].sons[0];j++)
			if(indt[pot[i].sons[j]]==0)
			{
				for(int k=j;k<=pot[i].sons[0]-1;k++)
				{
					pot[i].sons[k]=pot[i].sons[k+1];
				}
				pot[i].sons[0]--;j--;
			}
	}
}
void set_tree(int p,bool bel)
{
	for(int i=1;i<=pot[p].etop;i++)
	{
		int k=pot[p].edge[i];
		if(vis[k]==0)
		{
			pot[p].sons[++pot[p].sons[0]]=k;
			pot[k].dad=p;
			pot[k].deep=pot[p].deep+map[p][k];
			pot[k].belong=bel;
			vis[k]=1;
			set_tree(k,bel);
		}
	}
}
void reset_tree()
{
	for(int i=1;i<=n;i++)
		pot[i].dad=pot[i].sons[0]=0;
	memset(vis,0,sizeof(vis));
	vis[t1]=1;vis[t2]=1;
	pot[t2].belong=1;
	pot[t1].belong=0;
	set_tree(t1,0);
	if(t1!=t2) set_tree(t2,1);
}
void find_centre()
{
	int i=y,l=0;
	while(1)
	{
		if(map[i][pot[i].dad]+l>dt/2)
		{
			t1=i;t2=pot[i].dad;
			dt2=map[i][pot[i].dad]+l-dt/2;
			dt1=dt/2-l;
			break;
		}
		else if(map[i][pot[i].dad]+l==dt/2)
		{
			t1=t2=pot[i].dad;
			dt1=dt2=0;
			break;
		}
		else
		{
			l+=map[i][pot[i].dad];
			i=pot[i].dad;
		}
	}
//	printf("%d %d %d %d\n",t1,t2,dt1,dt2);
}
void dfs(int p,int sum,bool record)
{
	vis[p]=1;
	if(sum>maxl)
	{
		maxl=sum;
		maxi=p;
	}
	for(int i=1;i<=pot[p].etop;i++)
	{
		int k=pot[p].edge[i];
		if(vis[k]==0)
		{
			if(record==1)
			{
				pot[p].sons[++pot[p].sons[0]]=k;
				pot[k].dad=p;
			}
			int d=pot[p].dis[i];
			vis[k]=1;
			dfs(k,sum+d,record);
		}
	}
}
void find_first_d()
{
	dfs(1,0,0);
	x=maxi;
	maxi=maxl=0;
	memset(vis,0,sizeof(vis));
	dfs(x,0,1);
	y=maxi;
	dt=maxl;
}
int main()
{
//	freopen("core.in","r",stdin);
//	freopen("core.out","w",stdout);
	scanf("%d%d",&n,&s);
	s*=2;
	for(int i=1;i<=n-1;i++)
	{
		int st,ed,dis;
		scanf("%d%d%d",&st,&ed,&dis);
		pot[st].edge[++pot[st].etop]=ed;
		pot[st].dis[pot[st].etop]=dis*2;
		map[st][ed]=dis*2;
		pot[ed].edge[++pot[ed].etop]=st;
		pot[ed].dis[pot[ed].etop]=dis*2;
		map[ed][st]=dis*2;
	}
	find_first_d();
//	printf("%d %d",x,y);
	find_centre();
	reset_tree();
	cut_tree();
	if(find_same()==1) return 0;
	find_core();
	return 0;
}
