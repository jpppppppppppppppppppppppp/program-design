#include <iostream>
#include <vector>
using namespace std;
int main(){
	int n;
	cin >> n;
	int stone[2*n+2],f[2*n+2][2*n+2];
	for(int i=0;i<2*n+2;i++)
		for(int j=0;j<2*n+2;j++)f[i][j]=0;
	for(int i=0;i<n;i++){
		cin >> stone[i];
	}
	for(int i=n;i<2*n+2;i++){
		stone[i]=stone[i-n];
	}
	for(int len=1;len<n;len++){
		for(int i=0;i<n;i++){
			int j=i+len;
			for(int k=i;k<j;k++){
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+stone[i]*stone[j+1]*stone[k+1]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)ans=max(ans,f[i][i+n-1]);
	cout << ans << endl;
}