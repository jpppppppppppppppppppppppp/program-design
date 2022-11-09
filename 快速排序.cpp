#include <iostream>
using namespace std;
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}

int partition(int *A,int p,int r){
	int x = A[r], i = p-1;
	for(int j=p;j<=r-1;j++){
		if(A[j]<=x){
			i++;
			swap(A[i],A[j]);
		}
	}
	swap(A[i+1],A[r]);
	return i+1;
}

void quicksort(int *A, int p, int r){
	while(p<r){
		int q = partition (A,p,r);
		quicksort (A,p,q-1);
		p=q+1;
	}
}//尾递归

/*
 void quicksort(int *A, int p, int r){
	if(p<r){
		int q = partition (A,p,r);
		quicksort (A,p,q-1);
		quicksort (A,q+1,r);
	}
}
 */

int main(){
	int A[14]={4,-1,3,2,16,9,10,14,8,7,1,19,20,0};
	int len = sizeof(A)/sizeof(A[0]);
	quicksort (A,0,len-1);
	for(int i=0;i<len;i++){
		cout << A[i] << endl;
	}
}