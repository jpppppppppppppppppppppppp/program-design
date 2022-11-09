#include<iostream>
using namespace std;
void merge(int * data,int start,int mid, int end, int * result) {
	int i = start, j = mid + 1, k = 0;
	while (i <= mid and j <= end) {
		if (data[i] <= data[j])
		{result[k++] = data[i++];}
		else 
		{result[k++] = data[j++];}
	}
	while (i <= mid) 
	{result[k++] = data[i++];}
	while (j <= mid) 
	{result[k++] = data[j++];}
	for (int t = 0; t < k; t++)
	{data[start + t] = result[t];}
}
void mergesort(int* data, int start, int end, int* result) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergesort(data, start, mid, result);
		mergesort(data, mid + 1, end, result);
		merge(data, start, mid, end, result);
	}
}
int main() {
	int a[] = { 12,2,8,4,7,13,5,5,6,0 };
	int len = sizeof(a) / sizeof(a[0]);
	int * result = new int[len];
	mergesort(a, 0, len-1, result);
	for (int i = 0; i < len; i++) {
		cout << a[i] << endl;
	}
	return 0;
}