#include <cstdio>
int f[10][12];
int getans(int p,int bits)
{
	if(p==0) return 0;
	int ans=getans(p/10,bits+1);
	int bn=p%10,bl=(p%100)/10;
	for(int i=0;i<=bn-1;i++)
		if(bl!=0 && (bl==bn || bl==bn-1 || bl==bn+1)) continue;
		else ans+=f[i][bits];
	return ans;
}
int getans(int num)
{
	int bit=1,p=1,val,nowget=0,rez=0,lastbit=-1;
	while(p<=num) bit++,p*=10;
	p/=10;bit--;
	if(num/p!=1)
	{
		val=1;
		nowget=p;
		while(nowget+p<=num)
		{
			nowget+=p;
			rez+=f[val][bit];
			val++;
		}
	}
	while(bit>0)
	{
		val=1;
		while(nowget+p<num)
		{
			nowget+=p;
			rez+=f[
		}
	}
}
int main()
{
	int l,r;
	scanf("%d%d",&l,&r);
	for(int i=0;i<=9;i++) f[i][1]=1;
	for(int i=2;i<=10;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++)
				if(j==k || j==k+1 || j==k-1) continue;
				else f[j][i]+=f[k][i-1];
	printf("%d",getans(r+1,1)-getans(l,1));
	return 0;
}
