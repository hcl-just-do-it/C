#include<iostream>
using namespace std;
class Qatar2022{
	public:
	char name1[50],name2[50],date[50],stadium[50],score[50];
	Qatar(char name1[50],char name2[50],char date[50],char stadium[50],char score[50]){
		strcpy(this->name1, name1);
	}
	virtual void show() = 0;
};
class Group : public Qatar2022{
	public:
	Group(char name1[50],char name2[50],char date[50],char stadium[50],char score[50]){
		strcpy(this->name1, name1);
		strcpy(this->name2, name2);
		strcpy(this->date, date);
		strcpy(this->stadium, stadium);
		strcpy(this->score, score);
	}
	
	void show(){
		cout<<"Group show"<<endl;
		cout<<name1<<name2<<date<<stadium<<score<<endl;
	}
};
class Final : public Qatar2022{
	public:
	Final(char name1[50],char name2[50],char date[50],char stadium[50],char score[50]){
		strcpy(this->name1, name1);
		strcpy(this->name2, name2);
		strcpy(this->date, date);
		strcpy(this->stadium, stadium);
		strcpy(this->score, score);
	}
	void show(){
		cout<<"Final show"<<endl;
		cout<<name1<<name2<<date<<stadium<<score<<endl;
	}
};
int main(){
	char name1[50],name2[50],date[50],stadium[50],score[50];
	Qatar2022 *p1; 
	cin>>name1>>name2>>date>>stadium>>score;
	Group group1(name1,name2,date,stadium,score);
	cin>>name1>>name2>>date>>stadium>>score;
	Final final2(name1,name2,date,stadium,score);
	p1=&group1;
	p1->show();
	Qatar2022 &p2=final2;
	p2.show();
	return 0;
}