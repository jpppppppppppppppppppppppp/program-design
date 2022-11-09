#include <iostream>
#include <cmath>
using namespace std;
void counting_sort(int *A, int *B, int k, int len, int d){
	int *C=new int[k+1];
	for(int i=0;i<=k;i++)C[i]=0;
	for(int i=0;i<len;i++) {
		int w = (int) (A[i]/pow(10,d))%10;
		C[w+1]++;
	}
	for(int i=1;i<=k;i++)C[i]+=C[i-1];
	for(int i=0;i<len;i++){
		int w = (int) (A[i]/pow(10,d))%10;
		B[C[w]]=A[i];
		C[w]++;
	}
	for(int i=0;i<len;i++){
		A[i]=B[i];
	}
}
int main (){
	int A[30]={4,0,3,2,16,9,10,14,8,7,1,19,20,0,2,3,4,5,30,15,329,457,657,839,436,720,355,999,456,123};
	int max=3;//A中的每个元素的最大位数
	int len = sizeof (A)/sizeof (A[0]);
	int *B = new int[len];
	for(int i=0;i<len;i++)B[i]=A[i];
	for(int i=0;i<max;i++) {
		counting_sort (A, B, 10, len, i);
		for(int j=0;j<len;j++)cout << A[j] << " ";
		puts("");
	}
}