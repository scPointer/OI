//1-indexed
namespace heap{

int f[N];
int n;
inline void Swap(int& a,int& b)
{
	static int temp;
	temp=a;a=b;b=temp;
}
void merge(int a,int b)
{
	for(int x=a<<1;x<=b;x<<=1)
	{
		if(x<b && f[x]>f[x+1]) x++;
		if(f[a]<f[x]) break;
		swap(f[a],f[x]);
		swap(a,x);
	}
}
void pop()
{
	Swap(f[1],f[n]);
	merge(1,n-1);
	n--;
}
void init(int n)
{
	for(int i=n>>1;i>=1;i--)
		merge(i,n);
}

}
