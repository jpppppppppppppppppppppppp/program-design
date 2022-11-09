#include <iostream>
using namespace std;
template<typename T>
T pow(T base,int exp,__int128 MOD =19991231){
	long long cam[33];
	cam[0]=base%MOD;
	for(int i=1;i<=32;i++){
		__int128 a=(cam[i-1]*cam[i-1]);
		cam[i]=static_cast<long long>(a%MOD);
	}
	long long times = 0;
	__int128 s = 1;
	while(true){
		if(exp==0) {
			return static_cast<T>(s%MOD);
		}
		int c = exp - ((exp>>1)<<1);
		if(c==1){
			s*=cam[times];
			s%=MOD;
		}
		times ++;
		exp>>=1;
	}
}

int main() {
	long long a = 10;
	unsigned int b = 10;
	short c = 10;
	long int d = 10;
	cout << pow(a, 2) << " " << pow(b, 2) << " " << pow(c, 2) << " " << pow(d, 2) << " " << endl;
	return 0;
}
