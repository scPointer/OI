#include <cstdio>
#define N 5000005
int pos[N],val[N],top,lastans,q,mo;
int main()
{
	scanf("%d%d",&q,&mo);;
	char cr;
	for(int i=1,rd,sz=0,l,r,mid;i<=q;i++)
	{
		while((cr=getchar())!='Q' && cr!='A');
		scanf("%d",&rd);
		if(cr=='Q')
		{
			rd=sz-rd+1;
			l=1,r=top;
			while(l<r)
			{
				mid=(l+r)/2;
				if(pos[mid]<rd) l=mid+1;
				else r=mid;
			}
			printf("%d\n",lastans=val[l]);
		}
		else
		{
			rd=(rd+lastans)%mo;
			sz++;
			while(top>0 && val[top]<=rd) top--;
			top++;
			val[top]=rd;pos[top]=sz;
		}
	}
	return 0;
}
