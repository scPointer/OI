

//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <cmath>

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define PR(a,ed,name) for(int i=0;i<ed;i++) printf("%s[%d] %f, %f\n",name,i,a[i].x,a[i].y);

using namespace std;

typedef long long LL;

const int BUF_SIZE = (int)1e4 + 10;

struct fastIO
{
    char buf[BUF_SIZE];
    int cur;
    FILE *in, *out;
    fastIO()
    {
        cur = BUF_SIZE;
        in = stdin;
        out = stdout;
    }
    inline char nextChar()
    {
        if(cur == BUF_SIZE)
        {
            fread(buf, BUF_SIZE, 1, in);
            cur = 0;
        }
        return buf[cur++];
    }
    inline int nextInt()
    {
        int x = 0;
        char c = nextChar();
        while(!('0' <= c && c <= '9')) c = nextChar();
        while('0' <= c && c <= '9')
        {
            x = x * 10 + c - '0';
            c = nextChar();
        }
        return x;
    }
    inline void printChar(char ch)
    {
        buf[cur++] = ch;
        if (cur == BUF_SIZE)
        {
            fwrite(buf, BUF_SIZE, 1, out);
            cur = 0;
        }
    }
    inline void printInt(int x)
    {
        if (x >= 10) printInt(x / 10);
        printChar(x % 10 + '0');
    }
    inline void close()
    {
        if (cur > 0)
        {
            fwrite(buf, cur, 1, out);
        }
        cur = 0;
    }
} IO;

struct comp
{
	double x, y;

	comp(): x(0), y(0) { }
	comp(const double &_x, const double &_y): x(_x), y(_y) { }

};

inline comp operator+(const comp &a, const comp &b) { return comp(a.x + b.x, a.y + b.y); }
inline comp operator-(const comp &a, const comp &b) { return comp(a.x - b.x, a.y - b.y); }
inline comp operator*(const comp &a, const comp &b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline comp conj(const comp &a) { return comp(a.x, -a.y); }

const double PI = acos(-1);

const int maxn = 4;//262144;

int N;
int n, m;

comp a[maxn + 5], b[maxn + 5];
int c[maxn + 5];
int x[maxn + 5], y[maxn + 5];
int ans[maxn + 5];

comp w[maxn + 5];
int bitrev[maxn + 5];

inline void init()
{
	n = IO.nextInt(), m = IO.nextInt(), ++n, ++m;
	REP(i, 0, n) x[i] = IO.nextInt();
	REP(i, 0, m) y[i] = IO.nextInt();
}

void fft(comp *a, const int &n)
{
	REP(i, 0, n) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
	PR(a,n,"a");
	for (int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1)
		for (int j = 0; j < n; j += i)
		{
			comp *l = a + j, *r = a + j + (i >> 1), *p = w;
			REP(k, 0, i >> 1)
			{
				comp tmp = *r * *p;
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += lyc;
			}
		}
}

int main()
{
	init();
	int L = 0;
	for ( ; (1 << L) < n + m - 1; ++L);
	int N = 1 << L;
	REP(i, 0, N) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
	comp step = comp(cos(2 * PI / N), sin(2 * PI / N));
	w[0] = comp(1, 0);
	REP(i, 0, N) w[i + 1] = w[i] * step;
	REP(i, 0, N) a[i] = comp(x[i], y[i]);
	fft(a, N);
	REP(i, 0, N)
	{
		int j = (N - i) & (N - 1);
		b[i] = (a[j] * a[j] - conj(a[i] * a[i])) * comp(0, -0.25);
	}
	fft(b, N);
	REP(i, 0, n + m - 1) c[i] = (int)(b[i].x / N + 0.5);
	IO.cur = 0;
	REP(i, 0, n + m - 1) IO.printInt(c[i]), IO.printChar(' ');
    IO.printChar('\n');
    IO.close();
	return 0;
}

