#include <cstdio>
int main()
{
	double s=0,goal,each=2.0;
	int step=0;
	scanf("%lf",&goal);
	while(s+1e-9<goal)
	{
		s+=each;
		each*=0.98;
		step++;
	}
	printf("%d",step);
	return 0;
}
