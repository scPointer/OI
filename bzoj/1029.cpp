#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define N 150005
#define dMin(a,b) ((a)>(b)?(a)=(b):0)
struct Node{int ned,lim;}nd[N];
bool cmp(Node a,Node b)
{return a.lim==b.lim?a.ned<b.ned:a.lim<b.lim;}
priority_queue<int> q;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&nd[i].ned,&nd[i].lim);
	std::sort(nd+1,nd+1+n,cmp);
	long long sum=0;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(sum+nd[i].ned<=nd[i].lim)
			sum+=nd[i].ned,q.push(nd[i].ned),cnt++;
		else if(nd[i].ned<q.top())
		{sum+=nd[i].ned-q.top();q.pop();q.push(nd[i].ned);}
	}
	printf("%d",cnt);
}
