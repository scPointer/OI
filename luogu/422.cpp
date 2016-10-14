#include <cstdio>
int main()
{
	int a;
	double cost;
	scanf("%d",&a);
	if(a<=150) cost=a*0.4463;
	else if(a<=400) cost=150*0.4463+(a-150)*0.4663;
	else cost=150*0.4463+(400-150)*0.4663+(a-400)*0.5663;
	printf("%.01lf",cost+1e-8);
	return 0;
}
