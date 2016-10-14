#include <cstdio>
#define RN 35
#define MAXBIT 35
struct Matrix{int v[RN][RN];};
Matrix ans[2],map[MAXBIT];
int n,m,p,mreal;
void setmatrix(int q,Matrix& a)
//for judge which states can be shifted from state "q"
//I know the readability of this function is terrible
{
	int p=mreal^q;
	a.v[q][p]=1;
	int j,k;
	for(int i=0;i<=mreal;i++)
		if((i|p)==i)
		{
			j=i-p;
			k=3;
			while(k<=j)
			{
				if((k|j)==j) j-=k;
				k<<=1;
			}
			if(j==0) a.v[q][i]=1;
		}
}
void mult(Matrix& c,Matrix& a,Matrix& b)
//if reference is not be used, only one matrix for answer is enough, but that will slow down the program
{
	for(int i=0;i<=mreal;i++)
		for(int j=0;j<=mreal;j++)
		{
			c.v[i][j]=0;
			for(int k=0;k<=mreal;k++)
				c.v[i][j]=(c.v[i][j]+a.v[i][k]*b.v[k][j])%p;
			c.v[i][j]%=p;
		}
}
void assign(Matrix& a,Matrix& b)
{
	for(int i=0;i<=mreal;i++)
		for(int j=0;j<=mreal;j++)
			a.v[i][j]=b.v[i][j];
}
void print(Matrix& a)//function for test
{
	printf("\n");
	for(int i=0;i<=mreal;i++)
	{
		for(int j=0;j<=mreal;j++)
			printf("%d ",a.v[i][j]);
		printf("\n");
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	if(n%2==1 && m%2==1){printf("0");return 0;}
	//the improvement is not necessary, that means the program can run out correct answer without this line
	--n;//PAY ATTENTION TO THIS LINE
	mreal=(1<<m)-1;
	
	setmatrix(mreal,ans[0]);//wrong: setmatrix(0,ans[0]);
	//in fact the line cheat the function "setmatrix"
	for(int i=0;i<=mreal-1;i++)
		for(int j=0;j<=mreal;j++)
			ans[0].v[i][j]=ans[0].v[mreal][j];
	for(int i=0;i<=mreal;i++)
		setmatrix(i,map[0]);
	
	for(int i=2,j=1;i<=n;i<<=1,j++)
		mult(map[j],map[j-1],map[j-1]);
	int x=0;
	for(int i=1,j=0;i<=n;i<<=1,j++)
	{
		if(((n&i)&&1)==1)
		{
			x=1-x;
			mult(ans[x],ans[1-x],map[j]);//wrong: mult(ans[x],map[j],ans[1-x]);
			//(matrix)A * (matrix)B != (matrix)B * (matrix)A
		}
	}
	//the following four comment line are wrong
//	int rez=0;
//	for(int i=0;i<=mreal;i++)
//		rez=(rez+ans[x].v[i][mreal])%p;
//	printf("%d\n",rez);
	printf("%d\n",ans[x].v[0][mreal]);
	return 0;
}
