#include<iostream>
using namespace std;
int main() {
	int a[] = { 12,2,8,4,7,13,5,5 };
	int len = sizeof(a) / sizeof(a[0]);
	for (int i = 1; i < len; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 and a[j]>=key) {				//while (j >= 0 and a[j]<=key) {ÔòÎª½µÐò
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
	for (int i = 0; i < len; i++) {
		cout << a[i] << endl;
	}
	system("pause");
	return 0;
}