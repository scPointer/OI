#include <cstdio>

int main()
{
	FILE *ans,*out;
	ans=fopen("1036.ans","r");
	out=fopen("1036.out","r");
	freopen("1036_info.out","w",stdout);
	int a,b,i=0;
	while(fscanf(ans,"%d",&a)!=EOF)
	{
		fscanf(out,"%d",&b);
		i++;
		if(a!=b)
			printf("Line%d ans%d out%d\n",i,a,b);
	}
	fclose(ans);
	fclose(out);
}