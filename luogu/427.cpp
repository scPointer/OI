#include <cstdio>
int setnum[105];
int main()
{
	int top=0;
	while(1)
	{
		scanf("%d",&setnum[top]);
		if(setnum[top]==0) break;
		top++;
	}
	while(setnum[top]==0) top--;
	while(top>=0) printf("%d ",setnum[top--]);
	return 0;
}
