#include <cstdio>
#include <algorithm>
char s__[1<<18],*s_s,*s_t;
inline char gchar()
{
	if(s_s==s_t) s_s=s__,s_t=s_s+fread(s__,1,(1<<18)-5,stdin);
	return *s_s++;
}
inline int RD()
{
	int res=0,sign=1;
	char cr;
	while( (cr=gchar())<'0' || cr>'9')
		if(cr=='-') sign=-1;
	res=cr-'0';
	while( (cr=gchar())>='0' && cr<='9')
		res=res*10+cr-'0';
	return res*sign;
}
inline char RC(){char cr;while((cr=gchar())<'a' || cr>'z');return cr;}
#define N 300005
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
struct Temp{int id,len;}tp[N*2];
inline bool cmp(Temp a,Temp b){return a.len>b.len;}
struct Node{
	int fa;
	int len;
	int val;
	int nxt[26];
	bool isend;
	int soncnt;
	int son[26];
}nd[N*2];
int last,root,ndcnt;
int mn[N*2],mx[N*2],cnt[N*2];
long long ans[N][2];
int sc[N],v[N];
void add(int c,int v)
{
	int np=++ndcnt,p=last; last=np;
	nd[np].len=nd[p].len+1;
	nd[np].val=v;
	nd[np].isend=1;
	while(~p && nd[p].nxt[c]==0)
		nd[p].nxt[c]=np,p=nd[p].fa;
	if(p==-1) nd[np].fa=root;
	else
	{
		int q=nd[p].nxt[c];
		if(nd[q].len==nd[p].len+1) nd[np].fa=q;
		else
		{
			int nq=++ndcnt;
			nd[nq]=nd[q];nd[nq].len=nd[p].len+1;
			nd[nq].isend=0;
			nd[q].fa=nd[np].fa=nq;
			while(~p && nd[p].nxt[c]==q)
				nd[p].nxt[c]=nq,p=nd[p].fa;
		}
	}
}
void init()
{
	nd[root=last=0].fa=-1;
}
int main()
{
	init();
	int n=RD();
	for(int i=n;i>=1;i--) sc[i]=RC()-'a';
	for(int i=n;i>=1;i--) v[i]=RD();
	for(int i=1;i<=n;i++) add(sc[i],v[i]);
	for(int i=1;i<=ndcnt;i++)
		nd[nd[i].fa].son[nd[nd[i].fa].soncnt++]=i;
	for(int i=0;i<=ndcnt;i++) tp[i]=(Temp){i,nd[i].len};
	std::sort(tp,tp+1+ndcnt,cmp);
	long long ansc=0,ansmx=-(1ll<<62);
	int nowcalc=n-1;
	for(int i=0;i<=ndcnt;i++)
	{
		Node& p=nd[tp[i].id];
		int kp=tp[i].id;
		while(nowcalc>p.len)
		{
			ans[nowcalc][0]=ansc;
			ans[nowcalc][1]= ansc? ansmx: 0;
			nowcalc--;
		}
		bool fst=0;
		if(p.isend)
		{
			mn[kp]=mx[kp]=p.val;
			cnt[kp]=1;
			fst=1;
		}
		for(int i=0;i<p.soncnt;i++)
			if(p.son[i])
			{
				int np=p.son[i];
				if(fst)
				{
					ansmx=Max(ansmx,(long long)mx[kp]*mx[np]);
					ansmx=Max(ansmx,(long long)mn[kp]*mn[np]);
					ansc+=(long long)cnt[kp]*cnt[np];
					mn[kp]=Min(mn[kp],mn[np]);
					mx[kp]=Max(mx[kp],mx[np]);
					cnt[kp]+=cnt[np];
				}
				else
				{
					mn[kp]=mn[np];
					mx[kp]=mx[np];
					cnt[kp]=cnt[np];
					fst=1;
				}
			}
	}
	while(nowcalc>=0)
	{
		ans[nowcalc][0]=ansc;
		ans[nowcalc][1]=ansc? ansmx: 0;
		nowcalc--;
	}
	for(int i=0;i<=n-1;i++)
		printf("%lld %lld\n",ans[i][0],ans[i][1]);
}