#include <iostream>
using namespace std;
void counting_sort(int *A, int *B, int k, int len){
	int *C=new int[k+1];
	for(int i=0;i<=k;i++)C[i]=0;
	for(int i=0;i<len;i++)C[A[i]]++;
	for(int i=1;i<=k;i++)C[i]+=C[i-1];
	for(int i=len-1;i>=0;i--){
		B[C[A[i]]-1]=A[i];
		C[A[i]]--;
	}
}
int main(){
	int A[20]={4,0,3,2,16,9,10,14,8,7,1,19,20,0,2,3,4,5,30,15};
	int k=30;//A中的每个元素都小于k大于等于0且为整数
	int len = sizeof (A)/sizeof (A[0]);
	int *B = new int[len];
	for(int i=0;i<len;i++)B[i]=A[i];
	counting_sort (A,B,k,len);
	for(int i=0;i<len;i++)cout << B[i] << " ";
}