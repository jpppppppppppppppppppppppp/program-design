#include <iostream>
using namespace std;
inline bool check(int year){
	return (year%4==0 and year%100!=0) or (year%400==0);
}

int month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int month1[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
int monthm[13] = {0,31,31,28,31,30,31,30,31,31,30,31,30};
int monthm1[13] = {0,31,31,29,31,30,31,30,31,31,30,31,30};
int sum_day[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
int sum_day1[13] = {0,31,60,91,121,152,182,213,244,274,305,335,366};

class Calendar{
	int y=0;
	int m=0;
	int d=0;
public:

	Calendar():y(0),m(0),d(0){}
	Calendar(int year, int month, int day):y(year),m(month),d(day){}
	Calendar(std::string s){
		for(int i=0;i<4;i++)y=y*10+(s[i]-'0');
		for(int i=5;i<7;i++)m=m*10+(s[i]-'0');
		for(int i=8;i<10;i++)d=d*10+(s[i]-'0');
	}
	operator string() const{
		std::string temp = "0000-00-00";
		int ty = y;int tm = m;int td = d;
		for(int i=3;i>=0;i--){temp[i] = (ty%10)+'0';ty/=10;}
		for(int i=6;i>=5;i--){temp[i] = (tm%10)+'0';tm/=10;}
		for(int i=9;i>=8;i--){temp[i] = (td%10)+'0';td/=10;}
		return temp;
	}
	Calendar& operator=(const Calendar &b){
		y = b.y,m = b.m,d = b.d;
		return *this;
	}
	friend std::ostream& operator <<(std::ostream&oss, const Calendar&c){
		cout << string(c);
		return oss;
	};
	friend std::istream& operator >>(std::istream&iss,Calendar&c){
		string s;
		iss >> s;
		c = Calendar(s);
		return iss;
	};
	friend bool operator == (const Calendar &lhs,const Calendar &rhs){
		return lhs.y==rhs.y and lhs.m==rhs.m and lhs.d==rhs.d;
	}
	friend bool operator != (const Calendar &lhs,const Calendar &rhs){
		return !(lhs==rhs);
	}
	friend bool operator < (const Calendar &lhs,const Calendar &rhs){
		if(lhs.y!=rhs.y)return lhs.y < rhs.y;
		if(lhs.m!=rhs.m)return lhs.m < rhs.m;
		if(lhs.d!=rhs.d)return lhs.d < rhs.d;
		return false;
	}
	friend bool operator > (const Calendar &lhs,const Calendar &rhs){
		if(lhs.y!=rhs.y)return lhs.y > rhs.y;
		if(lhs.m!=rhs.m)return lhs.m > rhs.m;
		if(lhs.d!=rhs.d)return lhs.d > rhs.d;
		return false;
	}
	friend bool operator <= (const Calendar &lhs,const Calendar &rhs){
		return lhs < rhs or lhs == rhs;
	}
	friend bool operator >= (const Calendar &lhs,const Calendar &rhs){
		return lhs > rhs or lhs == rhs;
	}
	inline int getday(){
		int c = y/100;
		int tm=m;
		int ty = y%100;
		if(m<=2)tm+=12,ty=(y-1)%100,c=(y-1)/100;
		return (c/4-2*c+ty+ty/4+(13*(tm+1)/5)+d-1+7)%7;
	}

	friend Calendar operator +(const Calendar &c,int n){
		Calendar ans = c;
		if(n==0)return ans;
		if(n<0)return c-(-n);
		else{
			ans.d += n;
			while (true){
				if(ans.m > 12){
					ans.m -= 12;
					ans.y++;
				}
				if(check(ans.y)){
					if(month1[ans.m] < ans.d){
						ans.d -= month1[ans.m];
						ans.m++;
					}
					else break;
				}
				else{
					if(month[ans.m] < ans.d){
						ans.d -= month[ans.m];
						ans.m++;
					}
					else break;
				}
			}
			return ans;
		}
	}
	Calendar& operator +=(int n){
		*this = *this+n;
		return *this;
	}
	Calendar& operator ++(){
		*this = *this+1;
		return *this;
	}
	const Calendar  operator ++(int){
		Calendar temp = *this;
		*this = *this +1;
		return temp;
	}
	friend Calendar operator -(const Calendar &c,int n){
		Calendar ans = c;
		if(n==0)return ans;
		if(n<0)return c+(-n);
		else{
			ans.d -= n;
			while (true){
				if(ans.m <= 0){
					ans.m += 12;
					ans.y--;
				}
				if(check(ans.y)){
					if(ans.d <= 0){
						ans.d += monthm1[ans.m];
						ans.m--;
					}
					else break;
				}
				else{
					if(ans.d <= 0){
						ans.d += monthm[ans.m];
						ans.m--;
					}
					else break;
				}
			}
			return ans;
		}
	}
	Calendar& operator -=(int n){
		*this = *this-n;
		return *this;
	}
	Calendar& operator --(){
		*this = *this-1;
		return *this;
	}
	const Calendar  operator --(int){
		Calendar temp = *this;
		*this = *this -1;
		return temp;
	}
	friend int operator - (const Calendar &lhs,const Calendar &rhs){
		if(lhs==rhs)return 0;
		if(lhs<rhs)return -(rhs-lhs);
		else{
			if(lhs.y==rhs.y){
				if(check(lhs.y))return sum_day1[lhs.m-1]+lhs.d-sum_day1[rhs.m-1]-rhs.d;
				else return sum_day[lhs.m-1]+lhs.d-sum_day[rhs.m-1]-rhs.d;
			}
			else{
				int t_1,t_2,ans;
				if(check(rhs.y))t_1 = 366-sum_day1[rhs.m-1]-rhs.d;
				else t_1 = 365-sum_day[rhs.m-1]-rhs.d;
				if(check(lhs.y))t_2 = sum_day1[lhs.m-1]+lhs.d;
				else t_2 = sum_day[lhs.m-1]+lhs.d;
				ans = t_1+t_2;
				for(int i=rhs.y+1;i<lhs.y;i++)ans+=(365+check(i));
				return ans;
			}
		}
	}
};
const Calendar operator "" _C(const char *col, size_t n){
	return Calendar(col);
}
