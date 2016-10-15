#include <cstdio>
#define N 300005
int rd[N];
int cnt[N];
struct Node{int id,c;}nd[N];
int sum,rdsum;
int main()
{
	int n,q;
	int unread=0;
	scanf("%d%d",&n,&q);
	while(q--)
	{
		int tp,x;scanf("%d%d",&tp,&x);
		if(tp==1)
		{
			cnt[x]++;
			sum++;
			nd[sum].id=x;
			nd[sum].c=cnt[x];
			unread++;
		}
		else if(tp==2)
		{
			unread-=cnt[x]-rd[x];
			rd[x]=cnt[x];
		}
		else
		{
			while(rdsum<x && rdsum<=sum)
			{
				++rdsum;
				if(rd[nd[rdsum].id]<nd[rdsum].c)
					rd[nd[rdsum].id]++,unread--;
			}
		}
		printf("%d\n",unread);
	}
}
