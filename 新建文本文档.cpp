
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
class employee {
public:
	int number;
	string name;
	string sex;
	int birthtime;
	string post;
	int worktime;
	string title;
	int age;
	int workage;

	virtual int Read() = 0;
	virtual void Write() = 0;
	virtual void Display() = 0;
	virtual void Add() = 0;
	virtual void find() = 0;
	virtual void Delete() = 0;
	virtual void menu() = 0;
	virtual double arrage() = 0;
	virtual void Update() = 0;
};

class Faculty :public employee {
public:
	vector<Faculty>facultys;
	int Read();
	void Write();
	void Display();
	void Add();
	void find();
	void Delete();
	void menu();
	double arrage();
	void Update();
	//参考菜鸟教程
	friend istream& operator>>(istream& mycin, Faculty& t)
	{
		mycin >> t.number >> t.name >> t.sex >> t.birthtime >> t.post >> t.worktime >> t.title;//读取后存入vector容器中
		return mycin;
	}
	friend ostream& operator<<(ostream& mycout, const Faculty& t)
	{
		mycout << t.number << "\t" << t.name << "\t" << t.sex << "\t" << t.birthtime << "\t" << t.post << "\t" << t.worktime << "\t" << t.title << endl;//读取后存入vector容器中
		return mycout;
	}
};
class Staff :public employee {
public:
	vector<Staff>staffs;
	int Read();
	void Write();
	void Display();
	void Add();
	void find();
	void Delete();
	void menu();
	double arrage();
	void Update();
	//参考菜鸟教程
	friend istream& operator>>(istream& mycin, Staff& s)
	{
		mycin >> s.number >> s.name >> s.sex >> s.birthtime >> s.post >> s.worktime >> s.title;
		return mycin;
	}
	friend ostream& operator<<(ostream& mycout, const Staff& t)
	{
		mycout << t.number << "\t" << t.name << "\t" << t.sex << "\t" << t.birthtime << "\t" << t.post << "\t"
			<< t.worktime << "\t" << t.age << "\t" << t.title << endl;
		return mycout;
	}
};

void display_menu() {
	cout << "菜单如下：" << endl;
	cout << "1、显示所有" << endl;
	cout << "2、按Name查找" << endl;
	cout << "3、添加" << endl;
	cout << "4、删除" << endl;
	cout << "5、修改" << endl;
	cout << "6、平均Age和平均工龄" << endl;
	cout << "0、返回主菜单" << endl;
	cout << "请输入你的选项: ";
}

//教师
int Faculty::Read()//读取文件内的教师数据
{
	fstream readfile("faculty.txt");
	int tow = 0;
	if (readfile)
	{
		Faculty t;
		if (!(readfile >> t)) {
			cout << "\t空" << endl;
			return 1;
		}
		t.age = 2022 - t.birthtime / 10000;
		t.workage = 2022 - t.worktime;
		facultys.push_back(t);
		tow++;
		while (readfile >> t)//读取后存入vector容器中
		{
			t.age = 2022 - t.birthtime / 10000;
			t.workage = 2022 - t.worktime;
			tow++;
			facultys.push_back(t); //vector数组第要调用 push_back函数进行读入 
		}
		cout << "所有 信息加载成功......." << endl;
		readfile.close();
		return tow;
	}
	else
	{
		ofstream outfile;
		outfile.open("faculty.txt");
		if (!outfile.is_open())
		{
			cout << "文件没有创建!" << endl;
			return -1;
		}
		else
		{
			cout << "文件不存在，但是已经创建!\n";
			cout << "\t文件夹为空\n";
		}
		outfile.close();
	}
	return 2;
}
void Faculty::Write()
{
	ofstream outfile("faculty.txt");
	vector<Faculty>::iterator iter;
	for (iter = this->facultys.begin(); iter != this->facultys.end(); iter++)
	{
		//这里是迭代器指针，*号取指针的结构体数据，然后再重载运算符输出结构体
		outfile << *iter;
	}
	outfile.close();
}
void Faculty::menu()//教师管理端的菜单 
{
	int n1 = Read();//faculty总人数 
	while (1)
	{
		int n;
		display_menu();
		cin >> n;
		switch (n)
		{
		case 1:Display();  break;
		case 2:find();  break;
		case 3:Add();  break;
		case 4:Delete();  break;
		case 5:Update();  break;
		case 6: arrage();  break;
		case 0:return;
		}
	}
}
void Faculty::Display()
{
	vector<Faculty>::iterator iter;
	for (iter = this->facultys.begin(); iter != this->facultys.end(); iter++)
	{
		cout << "Number: " << iter->number << "\tName：" << iter->name << "\tSex：" << iter->sex << "\tBirthtime: " << iter->birthtime << "\nPost：" << iter->post << "\tWorktime："
			<< iter->worktime << "\tAge：" << iter->age << "\ttitle： " << iter->title << endl;
	}
}
void Faculty::Add()
{
	Faculty t;
	cout << "Input faculty Number："; cin >> t.number;
	cout << "Input faculty Name："; cin >> t.name;
	cout << "Input faculty Sex："; cin >> t.sex;
	cout << "Input faculty出生日期："; cin >> t.birthtime;
	cout << "Input faculty WorkTime："; cin >> t.worktime;
	cout << "Input faculty岗位："; cin >> t.post;
	cout << "Input faculty title："; cin >> t.title;
	t.age = 2022 - t.birthtime / 10000;
	t.workage = 2022 - t.worktime;
	facultys.push_back(t);
	this->Write();
}
void Faculty::Delete()
{
	if (facultys.empty()) { //调用empty函数判断数组是否为空 
		cout << "没有信息可以删除!" << endl;
		return;
	}
	string _name;
	cout << "Input facultyName: ";   cin >> _name;
	vector<Faculty>::iterator iter;
	for (iter = this->facultys.begin(); iter != this->facultys.end();)
	{
		if (iter->name == _name)
		{
			facultys.erase(iter);//调用erase函数对数组中元素进行删除 
			this->Write();
			cout << "删除成功！" << endl;
			return;
		}
		else
			++iter;
	}
}
void Faculty::Update()
{
	string name;
	cout << "Input想修改的faculty的Name： "; cin >> name;
	vector<Faculty>::iterator iter;
	for (iter = this->facultys.begin(); iter != this->facultys.end();)
	{
		if (iter->name == name)
		{
			cout << "Input faculty的岗位："; cin >> iter->post;
			cout << "Input faculty的title："; cin >> iter->title;
			this->Write();
			return;
		}
		else
			++iter;
	}
	cout << "未检索到此faculty!" << endl;
}
void Faculty::find()
{
	string _name;
	cout << "Input facultyName: ";   cin >> _name;
	vector<Faculty>::iterator iter;
	for (iter = this->facultys.begin(); iter != this->facultys.end(); iter++)
	{
		if (iter->name == _name)
		{
			cout << "Number: " << iter->number << "\tName：" << iter->name << "\tSex：" << iter->sex << "\n出生日期: " << iter->birthtime << "\t岗位：" << iter->post << "\tWorkTime："
				<< iter->worktime << "\tAge：" << iter->age << "\ttitle： " << iter->title << endl;
		}
	}
}
double Faculty::arrage()
{
	vector<Faculty>::iterator iter;//定义迭代器 
	double tsum = 0;
	double tsum2 = 0;
	for (iter = this->facultys.begin(); iter != this->facultys.end(); iter++)
	{
		tsum = tsum + iter->age;
		tsum2 = tsum2 + iter->workage;
	}
	cout << "平均年龄" << tsum / facultys.size() << " 平均工龄:" << tsum2 / facultys.size() << endl;
	return tsum;
}

//职工
int Staff::Read()
{
	fstream readfile("staff.txt");
	int wow = 0;
	if (readfile)
	{
		Staff w;
		if (!(readfile >> w)) {
			cout << "\t空" << endl;
			return 1;
		}
		w.age = 2022 - w.birthtime / 10000;
		w.workage = 2022 - w.worktime;
		staffs.push_back(w);
		wow++;
		while (readfile >> w) {
			wow++;
			w.age = 2022 - w.birthtime / 10000;
			w.workage = 2022 - w.worktime;
			staffs.push_back(w);
		}
		cout << "所有  信息加载成功......." << endl;
		readfile.close();
		return wow;
	}
	else
	{
		ofstream outfile;
		outfile.open("staff.txt");
		if (!outfile.is_open())
		{
			cout << "文件没有创建!" << endl;
			return -1;
		}
		else
		{
			cout << "文件不存在，但是已经创建!\n";
			cout << "\t文件夹为空\n";
		}
		outfile.close();
	}
	return 2;
}
void Staff::Write()
{
	ofstream outfile("staff.txt");
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end(); iter++)
	{
		outfile << iter->number << "\t" << iter->name << "\t" << iter->sex << "\t" << iter->birthtime << "\t" << iter->post << "\t"
			<< iter->worktime << "\t" << iter->title << endl;
	}
	outfile.close();
}
void Staff::menu()//工人管理端的菜单 
{
	int n2 = Read();
	while (1)
	{
		int n;
		display_menu();
		cin >> n;
		switch (n)
		{
		case 1:Display();  break;
		case 2:find();  break;
		case 3:Add();  break;
		case 4:Delete();  break;
		case 5:Update();  break;
		case 6:arrage();  break;
		case 0:return;
		}
	}
}
void Staff::Display()
{
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end(); iter++)
	{
		cout << "Number: " << iter->number << "\t Name：" << iter->name << "\tSex：" << iter->sex << "\tBirthtime: " << iter->birthtime << "\nPost：" << iter->post << "\tWorktime："
			<< iter->worktime << "\tAge：" << iter->age << "\ttitle：" << iter->title << endl << endl;
	}
}
void Staff::Add()
{
	Staff w;
	cout << "Input Worker Number："; cin >> w.number;
	cout << "Input Worker Name："; cin >> w.name;
	cout << "Input Worker Sex："; cin >> w.sex;
	cout << "Input Worker出生日期："; cin >> w.birthtime;
	cout << "Input WorkerWorkTime："; cin >> w.worktime;
	cout << "Input Worker岗位："; cin >> w.post;
	cout << "Input Worker岗位级别："; cin >> w.title;
	w.age = 2022 - w.birthtime / 10000;
	w.workage = 2022 - w.worktime;
	staffs.push_back(w);
	this->Write();
}
void Staff::Delete()
{
	if (staffs.empty()) {
		cout << "没有信息可以删除!" << endl;
		return;
	}
	string _name;
	cout << "Input facultyName: ";   cin >> _name;
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end();)
	{
		if (iter->name == _name)
		{
			staffs.erase(iter);
			this->Write();
			cout << "删除成功！" << endl;
			return;
		}
		else
			++iter;
	}
}
void Staff::Update()
{
	string name;
	cout << "Input想修改的Staff的Name： "; cin >> name;
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end();)
	{
		if (iter->name == name)
		{
			cout << "Input Staff的岗位："; cin >> iter->post;
			cout << "Input Staff的技术级："; cin >> iter->title;
			this->Write();
			return;
		}
		else
			++iter;
	}
	cout << "未检索到此Staff!" << endl;
}
void Staff::find()
{
	string _name;
	cout << "Input WorkerName: ";   cin >> _name;
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end(); iter++)
	{
		if (iter->name == _name)
		{
			cout << "Number: " << iter->number << "\t\tName：" << iter->name << "\tSex：" << iter->sex << "\n出生日期: " << iter->birthtime << "\t岗位：" << iter->post << "\tWorkTime："
				<< iter->worktime << "\tAge：" << iter->age << "\t技术级：" << iter->title << endl;
		}
	}
}
double Staff::arrage()
{
	double wsum = 0;
	double wsum2 = 0;
	vector<Staff>::iterator iter;
	for (iter = this->staffs.begin(); iter != this->staffs.end(); iter++)
	{
		wsum = wsum + iter->age;
		wsum2 = wsum2 + iter->workage;
	}
	cout << "平均年龄：" << wsum / staffs.size() << "平均工龄：" << wsum2 / staffs.size() << endl;
	return wsum;
}

int main()
{
	Faculty f;
	Staff s;
	while (1)
	{
		int n;
		cout << "  教职工管理系统 " << endl;
		cout << "  1、教师管理系统" << endl;
		cout << "  2、工人管理系统" << endl;
		cout << "  0、安全退出系统" << endl;
		cout << "请选择: "; cin >> n;
		switch (n)
		{
		case 1: f.menu();  break;
		case 2: s.menu();  break;
		case 0: return 0;
		}
	}
}
