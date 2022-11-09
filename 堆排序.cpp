#include <iostream>
using namespace std;
int left(int i){
	return 2*i+1;
}
int right(int i){
	return 2*i+2;
}
int parent(int i){
	return (i-1)/2;
}
void swap(int *a,int*b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void max_heapify(int *A,int i,int len){
	int l=left(i);
	int r=right(i);
	int largest;
	if(l<=len-1 and A[l]>A[i])largest=l;
	else largest = i;
	if(r<=len-1 and A[r]>A[largest])largest=r;
	if(largest!=i){
		swap(A[i],A[largest]);
		max_heapify (A,largest,len);
	}
}


void build_max_heap(int *A,int len){
	for(int i=parent(len-1);i>=0;i--)max_heapify (A,i,len);
}


int main(){
	int A[14]={4,-1,3,2,16,9,10,14,8,7,1,19,20,0};
	int len_1 ,len;
	len_1=len= sizeof(A)/sizeof (A[0]);
	build_max_heap (A,len);
	for(int i =len-1;i>=1;--i){
		swap(A[0],A[i]);
		len--;
		max_heapify (A,0,len);
		for(int j=0;j<len_1;j++){
			cout << A[j] <<" ";
		}
		puts("");
	}
	return 0;
}