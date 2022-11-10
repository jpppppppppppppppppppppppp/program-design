#ifndef SRC_HPP
#define SRC_HPP

namespace sjtu {
	template <class T>
	void sort(T* first, T* last){
		// TODO
		// O(nlogn)
		if(first +1 == last)return;
		auto swap = [](T* a,T* b){
			T temp = *a;
			*a = *b;
			*b = temp;
		};
		T* flag=last;
		flag--;
		T* i=first;T* j=first;
		for(j;j!=flag;j++){
			if(*j < *flag)swap(i,j),i++;
			if(!(*j < *flag) and !(*flag < *j))swap(i,j),i++;
		}
		swap(i,flag);
		sort(first,i);
		sort(i,last);
	}

	template <class T>
	T* lower_bound(T* first, T* last, const T& value) {
		// TODO
		// O(logn)
		T* it;
		if(*(last-1)<value)return last;
		int count = last - first;
		while(count>0){
			it = first;
			int step = count/2;
			T* that = it + step;
			if(*that < value){
				first = ++that;
				count -= step+1;
			}
			else count = step;
		}
		return first;
	}

	template <class T>
	T* upper_bound(T* first, T* last, const T& value) {
		// TODO
		// O(logn)
		if(value < *first or (!(value < *first) and !(*first < value))) return last;
		T* it;
		int count = last - first;
		while(count>0){
			it = first;
			int step = count/2;
			T* that = it + step;
			if(!(value < *that)){
				count -= step+1;
				first = ++that;
			}
			else 	count = step;
		}
		return first;
	}
}  // namespace sjtu
#endif