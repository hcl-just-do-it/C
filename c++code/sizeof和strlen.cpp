#include<iostream>
#include<cstring>
using namespace std;
int main(){
	char c1[] = "he";
	char c2[] = {'h','e','l','l','o'};
	char c3[6] = {"hello"};
	char *p = "hello";
	cout<<sizeof(c1)<<" "<<strlen(c1)<<endl;
	cout<<sizeof(c2)<<" "<<strlen(c2)<<endl;
	cout<<sizeof(c3)<<" "<<strlen(c3)<<endl;
	cout<<sizeof(p)<<" "<<strlen(p)<<endl;cout<<p[0]<<endl;
}