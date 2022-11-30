// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>

struct Wrapper {
	// todo: add definitions here
	void (*m)(std::string);
	void (*begin)();
	void (*after)();
	Wrapper * next= nullptr;
	Wrapper * pre = nullptr;
};
// todo: add definition for link list

Wrapper * head = new Wrapper;

Wrapper * t = head;


// todo: create()
Wrapper * create(void foo(std::string id),void before(),void after()){
	if(head == nullptr)head = new Wrapper,t=head;
	Wrapper * temp = new Wrapper;
	temp->pre = t;
	t->next = temp;
	t = t->next;

	t->m = foo;
	t->begin = before;
	t->after = after;
	return t;
}
// todo: remove()
void remove(Wrapper* w){
	if(w== nullptr)return;
	w->pre->next = w->next;
	if(w->next!= nullptr)w->next->pre = w->pre;
	else t=w->pre;
	delete w;
}
// todo: run()
void run(Wrapper*w,std::string s){
	if(w== nullptr)return;
	w->begin();
	w->m(std::move(s));
	w->after();
}
// todo: destroy()
void destroy(){
	while(head!= nullptr){
		Wrapper * temp = head->next;
		delete head;
		head = temp;
	}
}
#endif //Wrapper_CPP_Wrapper_HPP