    #include <cstdio>
    #include <ctime>
    #include <algorithm>
    #define mo 998244353
    #define N 200005
    #define reset(x,a,b,c,d) (x.v[0][0]=a,x.v[0][1]=b,x.v[1][0]=c,x.v[1][1]=d)
    typedef long long ll;
    namespace fastio
    {
    	#define BUF 100005
    /*	char __s[BUF],*_ss,*_st;
    	inline char gchar()
    	{
    		if(_ss==_st)
    		{
    			_ss=__s;
    			_st=_ss+fread(__s,sizeof(char),BUF-5,stdin);
    		}
    		return *_ss++;
    	}*/
    	inline int RD()
    	{
    		int res;
     
    		char cr;
    		while( (cr=getchar())<'0' || cr>'9');
    		res=cr-'0';
    		while( (cr=getchar())>='0' && cr<='9')
    			res=(res<<1)+(res<<3)+cr-'0';
    		return res;
    	}
    	#undef BUF
    }using namespace fastio;
     
    struct Matrix{int v[2][2];};
    void operator*=(Matrix& a,Matrix b)
    {
    	Matrix c;reset(c,0,0,0,0);
    	for(int i=0;i<2;i++)
    		for(int j=0;j<2;j++)
    			for(int k=0;k<2;k++)
    				c.v[i][j]=((ll)a.v[i][k]*b.v[k][j]+c.v[i][j])%mo;
    	a=c;
    }
    void operator-=(Matrix& a,Matrix b)
    {
    	for(int i=0;i<2;i++)
    		for(int j=0;j<2;j++)
    			a.v[i][j]=((ll)a.v[i][j]+mo-b.v[i][j])%mo;
    }
    void operator+=(Matrix& a,Matrix b)
    {
    	for(int i=0;i<2;i++)
    		for(int j=0;j<2;j++)
    			a.v[i][j]=((ll)a.v[i][j]+b.v[i][j])%mo;
    }
    Matrix ep[55];
    void init(int lim)
    {
    	reset(ep[0],1,0,0,1);
    	reset(ep[1],0,1,1,1);
    	for(int i=2,j=2;j<=lim;i++,j<<=1)
    	{
    		ep[i]=ep[i-1];
    		ep[i]*=ep[i-1];
    	}
    }
    Matrix getFib(int p)
    {
    	Matrix res;reset(res,1,0,0,1);
    	for(int i=1;p;i++,p>>=1)
    		if(p&1)
    			res*=ep[i];
    	return res;
    }
     
    struct Node{int tp,l,r,id;}nd[N];
    struct Tag{int val,pos,id;}tag[N];
    int ans[N];
    int addsum[N],querysum[N];
    int n,m;
    bool cmp(Tag a,Tag b){return a.pos!=b.pos? a.pos<b.pos :a.val>b.val;}
    void cdcdqqq(int l,int r)
    {
    	if(l>=r) return;
    	int mid=(l+r)>>1;
    	cdcdqqq(l,mid);
    	cdcdqqq(mid+1,r);
    	if(addsum[mid]-addsum[l-1]==0 || querysum[r]-querysum[mid]==0)
    		return;
    		
    	int cnt=0;
    	for(int i=l;i<=mid;i++)
    		if(nd[i].tp)
    		{
    			tag[++cnt]=(Tag){0,nd[i].l,i};
    			tag[++cnt]=(Tag){nd[i].r-nd[i].l+1,nd[i].r+1,i};
    		}
    	for(int i=mid+1;i<=r;i++)
    		if(!nd[i].tp)
    			tag[++cnt]=(Tag){-1,nd[i].l,i};
    	std::sort(tag+1,tag+1+cnt,cmp);
    	int posnow=0;
    	Matrix mtxnow;reset(mtxnow,0,0,0,0);
    	for(int i=1;i<=cnt;i++)
    	{
    		if(posnow<tag[i].pos)
    			mtxnow*=getFib(tag[i].pos-posnow),posnow=tag[i].pos;
    		if(tag[i].val>0)
    			mtxnow-=getFib(tag[i].val);
    		else if(tag[i].val==0)
    			mtxnow+=getFib(0);
    		else
    			ans[tag[i].id]=((ll)mtxnow.v[0][0]+mtxnow.v[0][1]+ans[tag[i].id])%mo;
    	}
    //	printf("solve %d %d\n",l,r);
    }
    int main()
    {
    	int c1=clock();
    	freopen("chenyao_fib_game.in","r",stdin);
    	freopen("chenyao_fib_game.out","w",stdout);
    	init(200050);
    	n=RD();m=RD();
    	for(int i=1,tp,l,r;i<=m;i++)
    	{
    		tp=RD();l=RD();
    		r= tp? RD():0;
    		nd[i]=(Node){tp,l,r,i};
    		
    		addsum[i]=addsum[i-1];
    		querysum[i]=querysum[i-1];
    		tp? addsum[i]++: querysum[i]++;
    	}
    	cdcdqqq(1,m);
    	for(int i=1;i<=m;i++)
    		if(!nd[i].tp)
    			printf("%d\n",ans[i]);
    	printf("time %d\n",clock()-c1);
    }