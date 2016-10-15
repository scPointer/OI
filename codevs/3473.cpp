#include <cstdio>
typedef long long ll;
bool noprm[1005];
void init(int lim)
{
	noprm[1]=1;
	for(int i=2;i<=lim;i++)
		if(noprm[i]==0 && (ll)i*i<=lim)
			for(int j=i*i;j<=lim;j+=i)
				noprm[j]=1;
}
int main()
{
	init(1000);
	int k;scanf("%d",&k);
	int sum=0,p=1,cnt=0;
	for(;sum<=k;sum+=p++,cnt++)
		while(noprm[p]) p++;
	printf("%d %d\n",sum-k,cnt);
}