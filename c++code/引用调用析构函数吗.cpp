#include<iostream>
using namespace std;
class A{
	public:
	int x = 1;
//	static int y = 1;
	const int z = 1;
	static const int q = 1;
	A(){
		cout<<"A construct"<<endl;
	}
	~A(){
		cout<<"A Destructor function"<<endl;
	}
};
int main(){
	A a = A();
	//A &b = a;//引用不会调用析构函数
	A b = a;//浅拷贝，析构函数调用两次
	
//	A* p = new A();
//	A* &pp = p;
//	delete p;
//	delete pp;
    return 0;
}