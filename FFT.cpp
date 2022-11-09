#include<cstdio>
#include<cmath>
const double Pi = acos(-1);
#define Max 1350000
using namespace std;
struct cp {
	cp(double xx = 0, double yy = 0) { x = xx, y = yy; }
	double x, y;
	cp operator + (cp const& b) const
	{
		return cp(x + b.x, y + b.y);
	}
	cp operator - (cp const& b)const
	{
		return cp(x - b.x, y - b.y);
	}
	cp operator * (cp const& b)const
	{
		return cp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
}f[Max], p[Max], sav[Max];
int n, m;
void fft(cp* f, int len, int flag) {
	if (len == 1)return;
	cp* fl = f, * fr = f + len / 2;
	for (int i = 0; i < len; i++)sav[i] = f[i];
	for (int i = 0; i < len / 2; i++) {
		fl[i] = sav[i << 1];
		fr[i] = sav[i << 1 | 1];
	}
	fft(fl, len / 2, flag); fft(fr, len / 2, flag);
	cp g(cos(2 * Pi / len), flag * sin(2 * Pi / len)), c(1, 0);
	for (int i = 0; i < len / 2; i++) {
		sav[i] = fl[i] + c * fr[i];
		sav[i + len / 2] = fl[i] - c * fr[i];
		c = c * g;
	}
	for (int i = 0; i < len; i++)f[i] = sav[i];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)scanf("%lf", &f[i].x);
	for (int i = 0; i <= m; i++)scanf("%lf", &p[i].x);
	for (m += n, n = 1; n <= m; n <<= 1);
	fft(f, n, 1); fft(p, n, 1);
	for (int i = 0; i <= n; i++)f[i] = f[i] * p[i];
	fft(f, n, -1);
	for (int i = 0; i <= m; i++)printf("%d ", (int)(f[i].x / n + 0.49));
	system("pause");
}