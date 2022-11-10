// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>

struct Wrapper {
	// todo: add definitions here
	void (*p)(std::string);
	void (*b)();
	void (*a)();
};


// todo: add definition for link list
struct list{
		Wrapper w;
		Wrapper* left;
		Wrapper* right;
};


// todo: create()
Wrapper* create(void foo(std::string),void before(),void after()){
	void (*p)(std::string);void (*b)();void (*a)();
	p =foo,b=before,a=after;
	static Wrapper w ={p,b,a};
	return &w;
}


// todo: remove()
void remove(Wrapper *f){

}


// todo: run()
void run(Wrapper *f, std::string s){

}


// todo: destroy()
void destroy(){

}
#endif //Wrapper_CPP_Wrapper_HPP