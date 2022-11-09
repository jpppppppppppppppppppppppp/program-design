#include<iostream>
using namespace std;
int main() {
	int a[] = { 12,2,8,4,7,13,5,5 };
	int len = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < len; i++) {
		int max = i;
		for (int j = i+1; j < len; j++) {
			if (a[j] >= a[max]) {
				max = j;
			}
			int temp = a[i];
			a[i] = a[max];
			a[max] = temp;
		}
	}
	for (int i = 0; i < len; i++) {
		cout << a[i] << endl;
	}
	system("pause");
	return 0;
}