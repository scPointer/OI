#include <cstdio>
#include <cmath>
#define PI acos(-1)
#define eps 1e-8
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
#define N 505
double x[N],r[N];
double ll[N],rr[N],k[N],b[N];
int lcnt;
int n;
double getf(double x0)
{
	double res=0,y0;
	for(int i=1;i<=n;i++)
		if(fabs(x0-x[i])<r[i]+eps)
		{
			y0=sqrt(r[i]*r[i]-(x0-x[i])*(x0-x[i]));
			res=Max(res,y0);
		}
	for(int i=1;i<=lcnt;i++)
		if(ll[i]<x0+eps && x0<rr[i]+eps)
		{
			y0=k[i]*x0+b[i];
			res=Max(res,y0);
		}
	return res;
}
inline double calc(double l,double r,double fl,double fmid,double fr)
{return (fl+4*fmid+fr)*(r-l)/6;}
double simpson(double l,double r,double fl,double fmid,double fr)
{
	double mid=(l+r)/2;
	double flmid=getf(l*0.75+r*0.25),frmid=getf(l*0.25+r*0.75);
	double simpl=calc(l,mid,fl,flmid,fmid);
	double simpr=calc(mid,r,fmid,frmid,fr);
	double simpall=calc(l,r,fl,fmid,fr);
	if(fabs(simpall-(simpl+simpr))<eps) return simpl+simpr;
	else return simpson(l,mid,fl,flmid,fmid)+simpson(mid,r,fmid,frmid,fr);
}
int main()
{
	double alpha,h,preh=0;
	scanf("%d%lf",&n,&alpha);n++;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&h);
		preh+=h;
		x[i]=(double)preh/tan(alpha);
	}
	for(int i=1;i<=n-1;i++)
		scanf("%lf",&r[i]);
	r[n]=0;
	double ml=x[1],mr=x[1];
	for(int i=1;i<=n;i++)
	{
		ml=Min(ml,x[i]-r[i]);
		mr=Max(mr,x[i]+r[i]);
	}
	double x1,x2,r1,r2;
	for(int i=1;i<=n-1;i++)
		if(fabs(x[i+1]-x[i])>fabs(r[i+1]-r[i])+eps)
		{
			x1=x[i],x2=x[i+1],r1=r[i],r2=r[i+1];
			lcnt++;
			if(fabs(r2-r1)<eps)
			{
				k[lcnt]=0;
				b[lcnt]=r1;
				ll[lcnt]=Min(x1,x2);
				rr[lcnt]=Max(x1,x2);
			}
			else
			{
				
				double d=(x1*r2-x2*r1)/(r1-r2);
				double d2=sqrt((x1+d)*(x1+d)-r1*r1);
				double y1=r1*d2/fabs(x1+d);
				k[lcnt]= r1<r2? r1/d2: -r1/d2;
				b[lcnt]=d*k[lcnt];
				ll[lcnt]=((r1*d2)/fabs(x1+d)-b[lcnt])/k[lcnt];
				rr[lcnt]=(r2*y1/r1 -b[lcnt])/k[lcnt];
			}
		}
	printf("%.02lf",simpson(ml,mr,0,getf((ml+mr)/2),0)*2);
}