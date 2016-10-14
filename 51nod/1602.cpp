#include <cstdio>
#define N 100000003
typedef long long ll;
bool noprm[N];
int prm[N],pcnt;
int mo[N];
void mobius(int lim)
{
	mo[1]=1;
	for(int i=2;i<=lim;i++)
	{
//		if(i%1000000==0) printf("run %d\n",i);
		if(noprm[i]==0)
		{
			mo[i]=-1;
			prm[++pcnt]=i;
		}
		for(int j=1;(ll)i*prm[j]<=lim && j<=pcnt;j++)
		{
			noprm[i*prm[j]]=1;
			if(i%prm[j]==0)
			{
				mo[i*prm[j]]=0;
				break;
			}
			mo[i*prm[j]]=-mo[i];
		}
	}
}
void solve(int val,int cnt)
{
	for(int i=0,c=0;;i++)
	{
		if(mo[i]==val) c++;
		if(c==cnt)
		{
			printf("%d",i);
			break;
		}
	}
}
int main()
{
	mobius(N-1);
/*	for(int i=1;i<=50;i++)
	{
		int tot=0;
		for(int j=i;j<=N-1;j+=i)
			tot+=mo[j];
		printf("for %d tot %d\n",i,tot);
	}
	*/
	int val,cnt;scanf("%d%d",&val,&cnt);
	solve(val,cnt);
}