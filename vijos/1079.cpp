#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 10000005
int dset[28];
char s[MAXN];
struct node{
	node(int v0=0):v(v0){}
	int v;
	friend bool operator<(node a,node b){return a.v>b.v;}
}times[28];
priority_queue<node> q;
int main()
{
	fgets(s,MAXN-5,stdin);
	while(strcmp(s,"END\n")!=0&&strcmp(s,"END")!=0)
	{
		memset(times,0,sizeof(times));
		int len=strlen(s);
		for(int i=0;i<=len-2;i++)
			if(s[i]=='_') times[26].v++;
			else times[s[i]-'A'].v++;
		int readin=0;
		for(int i=0;i<=26;i++)
			if(times[i].v!=0) {q.push(times[i]);readin++;}
		if(readin<2) printf("%d %d 8.0\n",(len-1)*8,len-1);
		else{
			int ra=0;
			while(1)
			{
				int ans=q.top().v;
				q.pop();
				if(q.empty()) break;
				ans+=q.top().v;
				q.pop();
				ra+=ans;
				q.push(ans);
	//			printf("%3d",q.top().v);
	//			q.pop();
			}
			printf("%d %d %0.1f\n",(len-1)*8,ra,(double)((len-1)*8)/(double)ra+1e-8);
		}
		fgets(s,MAXN-5,stdin);
	}
	return 0;
}
