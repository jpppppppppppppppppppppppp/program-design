#include <iostream>
using namespace std;
template<typename T>

T pow(T base,__int128 exp,__int128 MOD =19991231){
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
		__int128 c = exp - ((exp>>1)<<1);
		if(c==1){
			s*=cam[times];
			s%=MOD;
		}
		times ++;
		exp>>=1;
	}
}

int main(){
	long long n,x_0,p;
	cin >> n >> x_0 >> p;
	long long x=1;
	long long ans=0;
	for(int i=0;i<=n;i++){
		long long a,y,k;
		cin >> a >> y >> k;
		a = a % p;
		y = y % p;
		long long temp=0;
		for(int j=0;j<=k;j++){
			temp += pow(y,j,p);
			temp %= p;
		}
		ans = (ans + (((a*pow(x,i,p))%p)*temp)%p)%p;
		x *= x_0;
		x %= p;
	}
	cout << ans;
}