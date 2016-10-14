#include <cstdio>
#include <string>
using namespace std;
class RotatedClock{
	public:
	string getEarliest(int hourHand, int minuteHand){
		int a=hourHand,b=minuteHand;
		a%=30;b%=30;
		for(int i=1;i<=12;i++)
			if(check(a,b)) break;
			else a=(a+30)%360,b=(b+30)%360;
		return check(a,b)? 
	}
};
RotatedClock obj;
int main()
{
	int a,b;scanf("%d%d",&a,&b);
	printf("%s",obj.getEarliest(a,b));
}