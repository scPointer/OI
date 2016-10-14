#include <cstdio>
#include <cmath>
#define PI acos(-1)
#define N (1<<18)+10
#define LEN (int)(3e6+5)
inline int RD()
{
	static char cr;
	static int res;
	while((cr=getchar())<'0' || cr>'9') ;
	res=cr-'0';
	while((cr=getchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res;
}
struct cpx{
	private:
		double x,y;
	public:
		cpx(double x_=0,double y_=0):x(x_),y(y_){}
		inline friend cpx operator +(const cpx& a,const cpx& b){return cpx(a.x+b.x,a.y+b.y);}
		inline friend cpx operator -(const cpx& a,const cpx& b){return cpx(a.x-b.x,a.y-b.y);}
		inline friend cpx operator *(const cpx& a,const cpx& b){return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
		inline double getreal(){return x;}
};
cpx a[N],b[N],wi[N];
int n,m,bt,bbt,bitrev[N];
void FFT(cpx c[],int n,int inserve)
{
	cpx temp;
	for(int i=2,len=n/i;i<=n;i<<=1,len>>=1)
	{
		for(int j=0;j<n;j+=i)
		{
			for(int k=j,r=0;k<j+(i>>1);k++,r++)
			{
				temp=wi[(r*len*inserve+bt)%bt]*c[k+(i>>1)];
				c[k+(i>>1)]=c[k]-temp;
				c[k]=c[k]+temp;
			}
		}
//		printf("Round %d\n",i);
//		for(int j=0;j<n;j++)
//			printf("[%d] %f,%f\n",j,c[j].x,c[j].y);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(bt=1,bbt=31;bt<=n+m;bt<<=1,bbt--);
	for(int i=0;i<bt;i++)
		bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (30 - bbt));//from matthew99
	for(int i=0;i<=n;i++) a[bitrev[i]]=cpx(RD(),0);
	for(int i=0;i<=m;i++) b[bitrev[i]]=cpx(RD(),0);
	
	wi[0]=cpx(1,0);for(int i=1;i<=bt;i++)wi[i]=wi[i-1]*cpx(cos(2*PI/bt),sin(2*PI/bt));
	
	FFT(a,bt,1);
	FFT(b,bt,1);
	for(int i=0;i<bt;i++) b[i]=a[i]*b[i];
	for(int i=0;i<bt;i++) a[bitrev[i]]=b[i];
	FFT(a,bt,-1);
	for(int i=0;i<=n+m;i++)
		printf("%d ",(int)(a[i].getreal()/bt+0.5));
	return 0;
}
