#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
int _s,_ptr;
struct Node{
	int gst;
	int cst;
	double p;
}nd[25];
//double f[30][30][30];
double f[25][1<<12][25];
int kasane[13],posk[25],top;
int last[25];
vector<string> costo;
class NewItemShop{
	public:
	inline char gchar(){return _ptr<costo[_s].length()? costo[_s][_ptr++]:1;}
	inline int readInt(){
		int res;
		char cr;
		while( ((cr=gchar())<'0' || cr>'9')&& cr!=1);
		if(cr==1) return -1;
		res=cr-'0';
		while( (cr=gchar())>='0' && cr<='9')
			res=res*10+cr-'0';
		return res;
	}
	void init(vector<string>& sc){
		memset(posk,-1,sizeof(posk));
		memset(last,-1,sizeof(last));
		int n=sc.size();
		for(int i=1,tim;i<=n;i++){
			double temp=1;
			int _last=-1;
			int cnt=0;
			_s=i-1;_ptr=0;
			while((tim=readInt())!=-1){
				last[tim]=_last;_last=tim;
				nd[tim].gst=i;
				nd[tim].cst=readInt();
//				nd[tim].p=readInt()/100.0;
//				temp-=nd[tim].p;
				temp-=readInt()/100.0;
				nd[tim].p=temp;
				if(++cnt==2){kasane[posk[i]=top]=i;top++;}
			}
		}
	}
	double getMaximum(int swords, vector <string> customers){
		costo=customers;
		init(customers);
		for(int i=23;i>=0;i--)
			if(nd[i].gst==0){
				for(int j=0;j<(1<<top);j++)
					for(int k=0;k<=swords;k++)
						f[i][j][k]=f[i+1][j][k];
			}
			else if(posk[nd[i].gst]==-1){
				for(int j=0;j<(1<<top);j++)
					for(int k=0;k<=swords;k++){
//						f[i][j][k]=f[i+1][j][k]*(1-nd[i].p);
//						if(k>0) f[i][j][k]+=Max(f[i+1][j][k],f[i+1][j][k-1]+nd[i].cst)*nd[i].p;
//						else f[i][j][k]+=f[i+1][j][k]*nd[i].p;
						f[i][j][k]=f[i+1][j][k]*nd[i].p;
						if(k>0) f[i][j][k]+=Max(f[i+1][j][k],f[i+1][j][k-1]+nd[i].cst)*(1-nd[i].p);
						else f[i][j][k]+=f[i+1][j][k]*(1-nd[i].p);
					}
			}
			else{
				int pos=1<<posk[nd[i].gst];
				for(int j=0;j<(1<<top);j++)
					for(int k=0;k<=swords;k++){
						double la=(~last[i]? nd[last[i]].p: 1);
//						if(j==0 && k==0) printf("at%d: meet %lf other %lf\n",i,(la-nd[i].p)/la,nd[i].p/la);
						if((j&pos) || k==0) f[i][j][k]=f[i+1][j][k];
//						else f[i][j][k]=f[i+1][j][k]*(1-nd[i].p)+Max(f[i+1][j&pos][k],f[i+1][j&pos][k-1]+nd[i].cst)*nd[i].p;
						else f[i][j][k]=f[i+1][j][k]*nd[i].p/la+Max(f[i+1][j|pos][k],f[i+1][j|pos][k-1]+nd[i].cst)*(la-nd[i].p)/la;
					}
			}
		return f[0][0][swords];
	}
};
NewItemShop obj;
vector <string> vs;
int main()
{
	freopen("5152.in","r",stdin);
	int n; scanf("%d",&n);
	char s[200];
	fgets(s,200,stdin);
	while(fgets(s,200,stdin))
		vs.push_back(s);
	printf("%lf",obj.getMaximum(n,vs));
}
