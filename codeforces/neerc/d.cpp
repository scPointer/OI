#include <cstdio>
#define N 200005
#define LIM 100000
typedef long long ll;
int li[N],ti[N];
ll ans[N];
ll cnt;
int acnt;
int main()
{
	int n;
	ll r;
	scanf("%d%I64d",&n,&r);
	for(int i=1;i<=n;i++)
		scanf("%d",&li[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&ti[i]);
	for(int i=1;i<=n;i++)
		if(li[i]>ti[i])
		{puts("-1");return 0;}
	ll left=0;
	ll tim=0;
	for(int i=1;i<=n;i++)
	{
		if(left>=li[i])
		{
			left-=li[i];
			tim+=li[i];
			continue;
		}
		ll need=li[i]*2-ti[i];//it works even if need<0
		if(left>=need)
		{
			tim+=li[i]*2-left;
			left=0;
		}
		else if(cnt<=LIM)
		{
			tim+=left;
			need-=left;
			ll st=li[i]-need;
			tim+=(st-left)*2;
			ll pos;
			for(pos=0;pos<need;pos+=r)
				if(acnt<LIM)
					ans[++acnt]=tim+pos,++cnt;
				else ++cnt;
			tim+=need;
			left=pos-need;
		}
		else
		{
			tim+=left;
			need-=left;
			ll st=li[i]-need;
			tim+=(st-left)*2;
			ll times=(need-1)/r+1;
			ll pos=times*r;
			cnt+=times;
			tim+=need;
			left=pos-need;
		}
	}
	
	printf("%I64d\n",cnt);
	if(cnt>LIM)return 0;
	for(int i=1;i<=cnt;i++)
	{
		printf("%I64d",ans[i]);
		i<cnt? putc(' ',stdout):putc('\n',stdout);
	}
}