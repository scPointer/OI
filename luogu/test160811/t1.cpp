#include <cstdio>
#define rp 2333333
typedef long long ll;
long long sum[22][22];
long long pre[22][22];
long long cnt[22][22];
long long pc[22][22];
int main()
{
	int n;
	scanf("%d",&n);
	int x=0,y=0,z=0,rxa,rxc,rya,ryc,rza,rzc,x0,y0,xs,ys;
	scanf("%d%d%d%d%d%d",&rxa,&rxc,&rya,&ryc,&rza,&rzc);
	for(int i=1;i<=n;i++)
	{
		x=((ll)y*rxa+rxc)%rp;
		y=((ll)z*rya+ryc)%rp;
		z=((ll)x*rza+rzc)%rp;
		x0=x%20;xs=x%20*100+y%10*10+z%10;
		x=((ll)y*rxa+rxc)%rp;
		y=((ll)z*rya+ryc)%rp;
		z=((ll)x*rza+rzc)%rp;
		y0=x%20;ys=x%20*100+y%10*10+z%10;
		sum[x0][y0]+=xs+ys;
		cnt[x0][y0]++;
	}
	for(int i=19;i>=0;i--)
		for(int j=19;j>=0;j--)
		{
			pre[i][j]=pre[i][j+1]+pre[i+1][j]-pre[i+1][j+1]+sum[i][j];
			pc[i][j]=pc[i][j+1]+pc[i+1][j]-pc[i+1][j+1]+cnt[i][j];
		}
	long long ans1=0,ans2=0;
	for(int i=0;i<=18;i++)
		for(int j=0;j<=18;j++)
		{
			ans1+=(cnt[i][j]*(i+j+2)*100-sum[i][j])*pc[i+1][j+1]+(pre[i+1][j+1]-pc[i+1][j+1]*(i+j+2)*100)*cnt[i][j];
			ans2+=cnt[i][j]*pc[i+1][j+1];
		}
	double ra=ans2==0? 0:(double)ans1/ans2/100.0;
	printf("%.5lf",ra);
}
