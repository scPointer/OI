#include <cstdio>
#include <cmath>
#include <cstring>
#define MAXLEN 100005
char s[MAXLEN+5];
int dis[MAXLEN*2];
int front[MAXLEN*2];
int find(int l,int r,int p)
{
	int mid=(l+r)/2;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(dis[mid]>p)
			r=mid;
		else if(dis[mid]<p)
			l=mid;
		else return mid;
	}
	return mid;
}
int main()
{
	int t;
	scanf("%d",&t);
	fgets(s,MAXLEN,stdin);
	for(int aa=1;aa<=t;aa++)
	{
		memset(dis,0,sizeof(dis));
		memset(front,0,sizeof(front));
		fgets(s,MAXLEN,stdin);
		int len=strlen(s);
		s[--len]='\0';
		int sum=0;
//		long long sum=0;
		int place=0,distop=0,aft=0;
		for(int i=0;i<len;i++)
		{
			if(s[i]=='R'){dis[++distop]=place;sum+=place;front[distop]=sum;aft=0;}
			else if(s[i]=='B') {place++;aft++;}
		}
		for(int i=distop+1;i<=distop*2;i++)
		{
			dis[i]=dis[i-distop]+dis[distop]+aft;
			front[i]=front[i-1]+dis[i];
		}
//		int mid=find(1,distop,sum/(long long)distop);
		int min=-1;
		for(int i=1;i<=distop;i++)
		{
			if(i==1||dis[i]!=dis[i-1])
			{
				int sum=front[distop+i-1]-front[i-1];
				int mid=find(i,distop+i-1,sum/distop);
				if(dis[mid+1]*distop-sum<sum-dis[mid]*distop) mid++;
				int right=(front[distop+i-1]-front[mid])-(distop+i-1-mid)*dis[mid];
				int left=(mid-i+1)*dis[mid]-(front[mid]-front[i-1]);
				int ans=right+left;
				if(min==-1||ans<min)
					min=ans;
			}
		}
		if(min==-1) min=0;
		printf("Case #%d: %d\n",aa,min);
	}
	return 0;
}
