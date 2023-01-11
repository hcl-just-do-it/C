#include <iostream>
using namespace std;

void showValue(const int &val)
{
    cout << val << endl;
}

int main()
{//常变量在运行时并不是存放在只读内存区，因此只要在程序运行时获取到变量的地址，即可对其进行修改
    const int val = 10;
    int *ptr = (int *)&val;
    (*ptr)++;
    cout<<ptr<<endl;
	cout<<&val<<endl;
	cout<<*ptr<<endl;
	cout<<val<<endl;
    showValue(val);
    return 0;
}
