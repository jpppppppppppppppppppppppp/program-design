#include <iostream>
using namespace std;
void debugPrint(){cout << endl;}
template<typename Type, typename... Types>
void debugPrint(const Type&key,const Types &... keys){
	cout << key << " ";
	debugPrint(keys...);
}
int main(){
	debugPrint(1,"a",12,32, true);
}