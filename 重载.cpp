#include<iostream>
using namespace std;
class RunAroundLake{
	public:
	int second;
	char address1[40],address2[40],date[40];
	RunAroundLake(){
		strcpy(this->address1, "StudentCenter");
		strcpy(this->address2, "SouthLake");
		strcpy(this->date, "2014/1/1");
		this->second= 0;
	}
	RunAroundLake(char address1[40],char address2[40],char date[40],int second){
		strcpy(this->address1, address1);
		strcpy(this->address2, address2);
		strcpy(this->date, date);
		this->second= second;
	}
	friend bool operator < (const RunAroundLake &x,const RunAroundLake &y) {
	    return x.second < y.second;
	}
	 friend ostream &operator<<( ostream &output,const RunAroundLake &D )
      { 
         output<< D.address1<<D.address2<<D.date<<D.second<<endl;
         return output;            
      }
	void show(){
		cout<<address1<<" "<<address2<<" "<<date<<" "<<second<<endl;
	}
};
int main(){
	char address1[40],address2[40],date[40];
	int second;
	cin>>address1>>address2>>date>>second;
	RunAroundLake run1,run2(address1,address2,date,second);
	cin>>address1>>address2>>date>>second;
	RunAroundLake run3(address1,address2,date,second);
	run1.show();
	cout<<run2<<endl;
	if(run3<run2)
		cout<<"run3 win";
	else cout<<"run2 win";
	return 0;
}