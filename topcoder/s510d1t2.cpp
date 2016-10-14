#include <cstdio>
#define N 5000
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
long long lk[N],lcnt;
long long val[N],len[N],vcnt;
long long fst,last;
long long _a,_b;
class TheLuckyGameDivOne{
	public:
	long long getlucky(int p,int x){
		long long res=0,ep=1;
		for(int i=0;i<=x;i++){
			res+= ep*(p&(1<<i)? 7:4);
			ep*=10;
		}
		return res;
	}
/*	long long check(long long p)
	{
		long long l=1,r=lcnt+1,mid;
		while(l<r-1)
		{
			mid
		}
	}
	*/
	long long solve(int st,long long l){
		int minv=8000;
		long long sumlen=0;
		while(st<=vcnt && sumlen<l)
		{
			minv=Min(minv,val[st]);
			sumlen+=len[st];
			st++;
		}
		return st<=vcnt || (sumlen>=l)? minv: -1;
	}
	long long calc(long long l,long long r){
		long long res=0;
		fst=last=-1;
		int i;
		for(i=1;i<=lcnt;i++)
			if(lk[i]>r) break;
			else if(lk[i]>=l){
				res++;
				if(fst==-1) fst=i;
			}
		last=i-1;
		return res;
	}
	int find(long long a, long long b, long long jLen, long long bLen){
		_a=a;_b=b;
		for(int x=0;x<=9;x++)
			for(int i=0;i<(1<<(x+1));i++)
			if(getlucky(i,x)>b) break;
			else if(getlucky(i,x)>=a) lk[++lcnt]=getlucky(i,x);
		lk[++lcnt]=20000000005ll;
		
		long long l=a,r=a+bLen-1;
		val[++vcnt]=calc(l,r);
		while(r<=b)
		{
			long long nxt;
			if(fst>=0) nxt=Min(lk[fst]+1-l,lk[last+1]-r);
			else nxt=lk[last+1]-r;
			if(r+nxt>b){
				len[vcnt]=b-r+1;
				break;
			}
			l+=nxt;r+=nxt;
			len[vcnt]=nxt;
			val[++vcnt]=calc(l,r);
		}
		int res,ans=0;
		for(int i=1;i<=vcnt;i++){
			res=solve(i,jLen-bLen+1);
			ans=Max(ans,res);
		}
		return ans;
	}
};
TheLuckyGameDivOne obj;
int main()
{
	long long a,b,jLen,bLen;
	scanf("%lld%lld%lld%lld",&a,&b,&jLen,&bLen);
	printf("%d",obj.find(a,b,jLen,bLen));
}