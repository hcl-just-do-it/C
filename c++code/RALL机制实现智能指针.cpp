#include<iostream>
#include<stdio.h>
using namespace std;

template<class T>
class SmartPoint
{
    T* point;
public:
	SmartPoint(T *ptr = nullptr) :point(ptr) {}

	~SmartPoint() {
		if (point) {
			// 会调用point指向对象的的析构函数
			delete point;
		}
	}
	// 使用智能指针就像使用内部包裹的的对象一样
	T& operator*() { 
		return *point; 
	}

	T* operator->() { 
		return point; 
	}
};

class Demo {
    public:
        Demo() {
            printf("执行构造函数\n");
        }
        ~Demo() {
            printf("执行析构函数\n");
        }
        void show() {
			printf("hello\n");
		}
};

int main() {
    SmartPoint<Demo> smartPoint(new Demo());
    smartPoint->show();
    Demo &demo = *smartPoint;
	demo.show();
}
