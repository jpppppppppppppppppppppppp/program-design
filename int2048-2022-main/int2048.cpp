#include "int2048.hpp"
const double Pi = acos(-1);
struct cp {
	explicit cp(double xx = 0, double yy = 0){ x = xx, y = yy; }
	double x, y;
	cp operator +(cp const& b) const{
		return cp(x + b.x, y + b.y);
	}
	cp operator -(cp const& b) const{
		return cp(x - b.x, y - b.y);
	}
	cp operator *(cp const& b) const{
		return cp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};



void fft(cp* f, int len, int flag){
	std::vector<cp> omg;
	for(int i = 0; i < len; i++)omg.push_back(cp(cos(2 * Pi * i / len), flag * sin(2 * Pi * i / len)));
	int lim = 0;
	while ((1 << lim) < len) lim++;
	for(int i = 0; i < len; i++){
		int t = 0;
		for(int j = 0; j < lim; j++)
			if((i >> j) & 1) t |= (1 << (lim - j - 1));
		if(i < t)std::swap(f[i], f[t]);
	}

	for(int i = 2; i <= len; i *= 2){
		int m = i / 2;
		for(cp* p = f; p != f + len; p += i)
			for(int j = 0; j < m; j++){
				cp t = omg[len / i * j] * p[j + m];
				p[j + m] = p[j] - t;
				p[j] = p[j] + t;
			}
	}
}

sjtu::int2048::int2048(long long int x){
	num.clear();
	len = 0;
	bool flag = false;
	if(x < 0)flag = true, x = -x;
	if(x == 0)num.push_back(0), len = 0;
	else{
		while (x != 0){
			num.push_back(static_cast<int>(x % 10000));
			x /= 10000;
			len += 4;
		}
		int check = *(num.end() - 1);
		len -= 4;
		while (check != 0){
			check /= 10;
			len++;
		}
	}
	if(flag)len = -len;
}

sjtu::int2048::int2048(const std::string &s){
	num.clear();
	len = 0;
	bool flag = false;
	for(int i = static_cast<int>(s.length() - 1); i >= 0; i--){
		if(s[i] == '-')flag = true;
		else{
			int a = s[i] - '0';
			if(len % 4 == 0)num.push_back(a);
			else{
				for(int j = 0; j < (len % 4); j++)a *= 10;
				num[len / 4] += a;
			}
			len++;
		}
	}
	if(len == 1 and num[0] == 0)len = 0;
	else if(flag)len = -len;
}


sjtu::int2048::int2048(const sjtu::int2048 &a){
	num.clear();
	for(int i = 0; i < a.num.size(); i++)num.push_back(a.num[i]);
	len = a.len;
}

sjtu::int2048::int2048(){
	num.clear();
	len = 0;
	num.push_back(0);
	len = 0;
}

void sjtu::int2048::print() const{
	if(len == 0)putchar('0');
	else if(len < 0){
		putchar('-');
		for(long long i = ((-len - 1) / 4); i >= 0; i--){
			if(i == ((-len - 1) / 4))printf("%d", num[i]);
			else printf("%04d", num[i]);
		}
	}
	else
		for(long long i = ((len - 1) / 4); i >= 0; i--){
			if(i == (len - 1) / 4)printf("%d", num[i]);
			else printf("%04d", num[i]);
		}
}

void sjtu::int2048::read(const std::string &p){
	*this = sjtu::int2048(p);
}

sjtu::int2048 &sjtu::int2048::add(const sjtu::int2048 &b){
	int2048& a = *this;
	int2048 c = b;
	if(b.len == 0) return a;
	else if(b.len > 0){
		if(a.len == 0){
			a = b;
			return a;
		}
		else if(a.len > 0){
			int m = std::max(a.num.size(), c.num.size()) + 1;
			for(int i = a.num.size(); i < m; i++)a.num.push_back(0);
			a.len = m * 4;
			for(int i = 0; i < c.num.size(); i++)a.num[i] = a.num[i] + c.num[i];
			for(int i = 0; i < m - 1; i++)a.num[i + 1] += a.num[i] / 10000, a.num[i] %= 10000;
			while (a.num[m - 1] == 0){
				m--;
				a.len -= 4;
				a.num.pop_back();
			}
			int check = a.num[m - 1];
			a.len -= 4;
			while (check != 0){
				check /= 10;
				a.len++;
			}
			return a;
		}
		else{
			a.len = -a.len;
			a.minus(c);
			a.len = -a.len;
			return a;
		}
	}
	else{
		if(a.len == 0){
			a = b;
			return a;
		}
		else if(a.len > 0){
			c.len = -c.len;
			a.minus(c);
			return a;
		}
		else{
			a.len = -a.len;
			c.len = -c.len;
			a.add(c);
			a.len = -a.len;
			return a;
		}
	}
}

sjtu::int2048 sjtu::add(const sjtu::int2048 &a, const sjtu::int2048 &b){
	int2048 ans = a;
	ans.add(b);
	return ans;
}


sjtu::int2048 &sjtu::int2048::operator=(const int2048 &b){
	len = b.len;
	num.clear();
	for(int i = 0; i < b.num.size(); i++)num.push_back(b.num[i]);
	return *this;
}

sjtu::int2048 & sjtu::int2048::minus(const sjtu::int2048 &b){
	int2048& a = *this;
	int2048 c = b;
	if(b.len == 0)return a;
	else if(b.len < 0){
		c.len = -c.len;
		a.add(c);
		return a;
	}
	else{
		if(a.len == 0){
			a = b;
			a.len = -b.len;
			return a;
		}
		else if(a.len > 0){
			if(a == b){
				a = sjtu::int2048();
				return a;
			}
			else if(a > b){
				for(int i = 0; i < (c.len - 1) / 4 + 1; i++)a.num[i] = a.num[i] - c.num[i];
				int i = 0;
				while (i < (a.len - 1) / 4){
					while (a.num[i] < 0){
						a.num[i] += 10000;
						a.num[i + 1] -= 1;
					}
					i++;
				}
				a.len = ((a.len - 1) / 4 + 1) * 4;
				while (a.num[a.len / 4 - 1] == 0){
					a.len -= 4;
					a.num.erase(a.num.end() - 1);
				}
				int check = a.num[a.len / 4 - 1];
				a.len -= 4;
				while (check > 0){
					check /= 10;
					a.len++;
				}
				return a;
			}
			else{
				int2048 temp = a;
				a = b;
				a.minus(temp);
				a.len = -a.len;
				return a;
			}
		}
		else{
			a.len = -a.len;
			a.add(b);
			a.len = -a.len;
			return a;
		}
	}
}

bool sjtu::operator==(const sjtu::int2048 &a, const sjtu::int2048 &b){
	if(a.len != b.len)return false;
	else{
		if(a.len == 0)return true;
		else if(a.len > 0){
			for(int i = (a.len - 1) / 4; i >= 0; i--){
				if(a.num[i] != b.num[i])return a.num[i] == b.num[i];
			}
			return true;
		}
		else{
			for(int i = (-a.len - 1) / 4; i >= 0; i--){
				if(a.num[i] != b.num[i])return a.num[i] == b.num[i];
			}
			return true;
		}
	}
}

bool sjtu::operator<(const sjtu::int2048 &a, const sjtu::int2048 &b){
	if(a.len != b.len)return a.len < b.len;
	else{
		if(a.len == 0)return false;
		else if(a.len > 0){
			for(int i = (a.len - 1) / 4; i >= 0; i--){
				if(a.num[i] != b.num[i])return a.num[i] < b.num[i];
			}
			return false;
		}
		else{
			for(int i = (-a.len - 1) / 4; i >= 0; i--){
				if(a.num[i] != b.num[i])return a.num[i] > b.num[i];
			}
			return false;
		}
	}
}

bool sjtu::operator>(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return b < a;
}

sjtu::int2048 sjtu::minus(const sjtu::int2048 &a, const sjtu::int2048 &b){
	int2048 temp = int2048(a);
	temp.minus(b);
	return temp;
}

sjtu::int2048 sjtu::operator+(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return add(a, b);
}

std::ostream &sjtu::operator<<(std::ostream &os, const sjtu::int2048 &a){
	a.print();
	return os;
}

std::istream &sjtu::operator>>(std::istream &in, sjtu::int2048 &a){
	std::string num;
	in >> num;
	a = int2048(num);
	return in;
}

bool sjtu::operator!=(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return !(a == b);
}

bool sjtu::operator<=(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return (a < b or a == b);
}

bool sjtu::operator>=(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return (a > b or a == b);
}

sjtu::int2048 &sjtu::int2048::operator+=(const sjtu::int2048& a){
	this->add(a);
	return *this;
}

sjtu::int2048 sjtu::operator-(const sjtu::int2048 &a, const sjtu::int2048 &b){
	return minus(a, b);
}

sjtu::int2048 &sjtu::int2048::operator-=(const sjtu::int2048& a){
	this->minus(a);
	return *this;
}

sjtu::int2048 sjtu::operator *(const sjtu::int2048& a, const sjtu::int2048& b){
	int2048 c = a, d = b;
	bool flag = false;
	if(a.len < 0) flag = 1 - flag, c.len = -c.len;
	if(b.len < 0) flag = 1 - flag, d.len = -d.len;
	if(c.len == 0 or d.len == 0)return 0;
	std::vector<long long> tem;
	int m = static_cast<int>(c.num.size()), n = static_cast<int>(d.num.size());
	for(m += n, n = 1; n <= m; n <<= 1);
	int2048 ans;
	ans.num.clear();
	ans.len = 4 * n;
	cp* f = new cp[n], * p = new cp[n];
	for(int i = 0; i < n; i++){
		f[i] = cp(0, 0);
		p[i] = cp(0, 0);
	}
	for(int i = 0; i < c.num.size(); i++){
		cp temp;
		temp.y = 0;
		temp.x = static_cast<double >(c.num[i]);
		f[i] = temp;
	}
	for(int i = 0; i < d.num.size(); i++){
		cp temp;
		temp.y = 0;
		temp.x = static_cast<double >(d.num[i]);
		p[i] = temp;
	}
/*	for (int i = 0; i < a.num.size(); i++)printf("%d ", (int)f[i].x);
	puts("");
	for (int i = 0; i < a.num.size(); i++)printf("%d ", a.num[i]);
	puts("");
	for (int i = 0; i < b.num.size(); i++)printf("%d ", (int)p[i].x);
	puts("");
	for (int i = 0; i < b.num.size(); i++)printf("%d ", b.num[i]);
	puts("");*/

	fft(f, n, 1), fft(p, n, 1);
	for(int i = 0; i < n; i++)f[i] = f[i] * p[i];
	fft(f, n, -1);
	for(int i = 0; i < n; i++)tem.push_back(static_cast<long long>(f[i].x / n + 0.49));
	delete[] f;
	delete[] p;

	for(int i = 0; i < n - 1; i++){
		tem[i + 1] += tem[i] / 10000;
		tem[i] %= 10000;
	}
	while (tem[ans.len / 4 - 1] <= 0){
		ans.len -= 4;
		tem.erase(tem.end() - 1);
	}
	int check = tem[ans.len / 4 - 1];
	ans.len -= 4;
	while (check > 0){
		check /= 10;
		ans.len++;
	}
	if(flag)ans.len = -ans.len;
	for(int i = 0; i < tem.size(); i++)ans.num.push_back(static_cast<int>(tem[i]));
	return ans;
}

sjtu::int2048 sjtu::operator /(const sjtu::int2048& a, const sjtu::int2048& b){
	if(a.len == 0)return 0;
	else{
		int2048 c = a, d = b, ans = 0;
		bool flag = false;
		if(c.len < 0)flag = 1 - flag, c.len = -c.len;
		if(d.len < 0)flag = 1 - flag, d.len = -d.len;
		while (c.num.size() > 2 * d.num.size())
			c.len += 4, d.len += 4, c.num.insert(c.num.begin(), 0), d.num.insert(d.num.begin(), 0);
		int2048 dd = c * ~d;
		for(int i = 0; i < 2 * d.num.size(); i++)dd.num.erase(dd.num.begin()), dd.len -= 4;
		if((dd + 1) * d < c)dd += (c - d * dd) / d;
		if((dd + 1) * d == c)dd += 1;
		while (dd * d > c)dd -= 1;

		if(flag)dd.len = -dd.len;
		return dd;
	}
}

sjtu::int2048& sjtu::int2048::operator *=(const sjtu::int2048&a){
	*this = *this * a;
	return *this;
}

sjtu::int2048 sjtu::operator ~(const int2048& b){
	int n = b.num.size();
	long long base = 10000;
	if(n == 1)return {base * base / b.num[0]};
	if(n == 2)return {base * base * base * base / (b.num[0] + b.num[1] * base)};
	else{
		int2048 bas = 1;
		for(int i = 0; i < 2 * n; i++)bas.num.insert(bas.num.begin(), 0), bas.len += 4;
		int k = (n + 2) / 2;
		int2048 c = b;
		for(int i = 0; i < n - k; i++)c.num.erase(c.num.begin()), c.len -= 4;
		int2048 ans = ~c;
		int2048 temp_1 = 2 * ans;
		for(int i = 0; i < n - k; i++)temp_1.num.insert(temp_1.num.begin(), 0), temp_1.len += 4;
		int2048 temp_2 = b * ans * ans;
		for(int i = 0; i < 2 * k; i++)temp_2.num.erase(temp_2.num.begin()), temp_2.len -= 4;
		ans = temp_1 - temp_2;
		return ans;
	}
}

sjtu::int2048& sjtu::int2048::operator /=(const sjtu::int2048&a){
	*this = *this / a;
	return *this;
}