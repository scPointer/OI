#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define H 2015
#define N 105
struct hei{
	bool reach;
	int front;
	int nowused;
}prih[H],h[H];
int quartz[N];
//int af[H];
bool used[N];
int n,sumh;
bool cmp(int a,int b){return a>b;}
void deletequartz(hei pb[],int height)
{
//	memset(used,0,sizeof(used));
	int p=height;
	while(pb[p].front!=-1)
	{
		used[pb[p].nowused]=1;
//		p=p-quartz[pb[p].nowused];
		p=pb[p].front;
	}
}
bool packback(hei pb[],int height)
{
//	memset(pb,0,sizeof(pb));
	pb[0].reach=1;
	pb[0].front=-1;
	for(int i=1;i<=n;i++)
	{
		if(used[i]==1) continue;
		for(int j=height;j>=quartz[i];j--)
			if(pb[j].reach==0&&pb[j-quartz[i]].reach==1)
			{
				pb[j].reach=1;
//				pb[j].front=pb[j-quartz[i]].nowused;
				pb[j].front=j-quartz[i];
				pb[j].nowused=i;
			}
	}
	return pb[height].reach;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&quartz[i]);
		sumh+=quartz[i];
//		af[quartz[i]]=i;
	}
	sort(quartz+1,quartz+n+1,cmp);
	packback(prih,sumh);
	for(int i=sumh;i>0;i--)
	{
		if(prih[i].reach==0) continue;
		memset(used,0,sizeof(used));
		memset(h,0,sizeof(h));
		deletequartz(prih,i);
		if(packback(h,i)==1)
		{printf("%d",i);return 0;}
	}
	printf("Impossible");
	return 0;
}
