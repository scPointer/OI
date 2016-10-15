#include <cstdio>
#include <vector>
#define N 300005
#define pb push_back
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
using namespace std;
typedef long long ll;
vector<int> plu[N],minu[N];
bool used[N];
ll ans[N];
int px[N],py[N];
int main()
{
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&px[i],&py[i]);
		plu[px[i]+py[i]].pb(i);
		minu[px[i]-py[i]+100000].pb(i);
	}
	int x0=0,y0=0,dir=0;
	ll nowt=0;
	while(1)
	{
		int dt;
		if(dir==0)
		{
			dt=Min(n-x0,m-y0);
			int p=x0-y0+100000;
			for(int i=minu[p].size()-1;i>=0;i--)
			{
				int pt=minu[p][i];
				if(!used[pt])
					used[pt]=1,ans[pt]=nowt+px[pt]-x0;
			}
			x0+=dt;
			y0+=dt;
			if(x0==n && y0==m) break;
			if(x0==n) dir=3;
			if(y0==m) dir=1;
		}
		else if(dir==1)
		{
			dt=Min(n-x0,y0);
			int p=x0+y0;
			for(int i=plu[p].size()-1;i>=0;i--)
			{
				int pt=plu[p][i];
				if(!used[pt])
					used[pt]=1,ans[pt]=nowt+px[pt]-x0;
			}
			x0+=dt;
			y0-=dt;
			if(x0==n && y0==0) break;
			if(x0==n) dir=2;
			if(y0==0) dir=0;
		}
		else if(dir==2)
		{
			dt=Min(x0,y0);
			int p=x0-y0+100000;
			for(int i=minu[p].size()-1;i>=0;i--)
			{
				int pt=minu[p][i];
				if(!used[pt])
					used[pt]=1,ans[pt]=nowt-px[pt]+x0;
			}
			x0-=dt;
			y0-=dt;
			if(x0==0 && y0==0) break;
			if(x0==0) dir=1;
			if(y0==0) dir=3;
		}
		else if(dir==3)
		{
			dt=Min(x0,m-y0);
			int p=x0+y0;
			for(int i=plu[p].size()-1;i>=0;i--)
			{
				int pt=plu[p][i];
				if(!used[pt])
					used[pt]=1,ans[pt]=nowt+py[pt]-y0;
			}
			x0-=dt;
			y0+=dt;
			if(x0==0 && y0==m) break;
			if(x0==0) dir=0;
			if(y0==m) dir=2;
		}
		nowt+=dt;
	}
	for(int i=1;i<=k;i++)
		if(ans[i]==0) printf("-1\n");
		else printf("%I64d\n",ans[i]);
}
