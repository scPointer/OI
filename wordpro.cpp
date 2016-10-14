#include <cstdio>
#include <cstring>
#include <algorithm>
#define LEN_WORD 30
#define LEN_DESCRIB 100
using namespace std;
struct Node{
	int val1,val2,val3;
	char describ[LEN_DESCRIB];
	char word[LEN_WORD];
	void readinword(char* s){int i=0;while(i<LEN_WORD-1 && *(s+i)!='\0') *(word+i++)=*(s+i);word[i]='\0';}
	void print(){puts(word);}
};
int main()
{
//	freopen("source.in","r",stdin);
	char s[LEN_WORD];
	Node nd;
	scanf("%s",s);
	nd.readinword(s);
	nd.print();
}