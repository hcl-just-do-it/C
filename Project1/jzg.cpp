#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <random>
#include <fstream>
using namespace std;
const int ACCOUNT_LENGTH = 7; // Length of the expert's account
const int PASSWORD_LENGTH = 6; // Length of the expert's password

// Structure to store the expert's information
struct Expert {
	std::string name;
	std::string gender;
	std::string position;
	std::string phoneNumber;
	std::string IDNumber;
	std::string account;
	std::string password;
};

// Structure to store the player's information
struct Player {
	std::string teacherID;
	std::string name;
	std::string college;
	std::string category;
	double cgbg;
	double ktsj;
	double jxln;
	double total;
};

// Function to generate a random password
std::string generatePassword() {
	static std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<> distribution(0, characters.size() - 1);

	std::string password;
	for (int i = 0; i < PASSWORD_LENGTH; i++) {
		password += characters[distribution(generator)];
	}
	return password;
}

bool cmp(Player p1, Player p2) {
	return p1.total > p2.total;
}
int main() {
	vector< Expert> experts;

	vector< Player > players;

	while (1) {
		int choice;
		std::cout << "0. exit system\n1. Expert entry\n2. Player entry\n3. grade\nEnter your choice: ";
		std::cin >> choice;
		if (choice == 0) {
			break;
		}
		if (choice == 1) {
			// Expert entry
			Expert expert;
			std::cout << "Enter expert name: ";
			std::cin >> expert.name;
			std::cout << "Enter expert gender: ";
			std::cin >> expert.gender;
			std::cout << "Enter expert position: ";
			std::cin >> expert.position;
			std::cout << "Enter expert phone number: ";
			std::cin >> expert.phoneNumber;
			std::cout << "Enter expert ID number: ";
			std::cin >> expert.IDNumber;

			// Generate expert's account and password
			int count = experts.size() + 1; // Number of experts already registered
			expert.account = "PSZJ";
			if (count < 10) {
				expert.account += "00";
			}
			else if (count < 100) {
				expert.account += "0";
			}
			expert.account += std::to_string(count);
			expert.password = generatePassword();

			// Add expert to the map
			experts.push_back(expert);
			std::cout << "Expert registered successfully\n";
			std::cout << "Account: " << expert.account << "\n";
		}
		else if (choice == 2) {
			// Player entry
			Player player;
			std::cout << "Enter player teacherID: ";
			std::cin >> player.teacherID;
			std::cout << "Enter expert name: ";
			std::cin >> player.name;
			std::cout << "Enter expert college: ";
			std::cin >> player.college;
			std::cout << "Enter expert category: ";
			std::cin >> player.category;



			// Add category to the map
			players.push_back(player);
			std::cout << "Player registered successfully\n";
			std::cout << "name: " << player.name << "\n";
		}
		else if (choice == 3) {
			cout << "start 理工科 grade" << endl;
			for (int i = 0; i < players.size(); i++) {
				if (players[i].category != "理工科")	continue;
				cout << "当前选手的名字是:" << players[i].name << endl;
				players[i].cgbg = 0; players[i].ktsj = 0; players[i].jxln = 0;
				double x, y, z;
				for (int j = 0; j < experts.size() / 2; j++) {
					cout << "当前专家的名字是：" << experts[j].name << endl;
					cout << "请输入成果报告分数:";
					cin >> x; players[i].cgbg += x;
					cout << "请输入课堂设计分数:";
					cin >> y; players[i].ktsj += y;
					cout << "请输入教学设计分数:";
					cin >> z; players[i].jxln += z;
				}
				players[i].cgbg /= (experts.size() / 2);
				players[i].ktsj /= (experts.size() / 2);
				players[i].jxln /= (experts.size() / 2);
				players[i].total = players[i].cgbg + players[i].ktsj + players[i].jxln;
				//cout << players[i].cgbg << " " << players[i].ktsj << " " << players[i].jxln << " " << players[i].total << endl;
			}
			cout << "start 人文经管 grade" << endl;
			for (int i = 0; i < players.size(); i++) {
				if (players[i].category == "理工科")	continue;
				cout << "当前选手的名字是:" << players[i].name << endl;
				players[i].cgbg = 0; players[i].ktsj = 0; players[i].jxln = 0;
				double x, y, z;
				for (int j = experts.size() / 2; j < experts.size(); j++) {
					cout << "当前专家的名字是：" << experts[j].name << endl;
					cout << "请输入成果报告分数:";
					cin >> x; players[i].cgbg += x;
					cout << "请输入课堂设计分数:";
					cin >> y; players[i].ktsj += y;
					cout << "请输入教学设计分数:";
					cin >> z; players[i].jxln += z;
				}
				players[i].cgbg /= (experts.size() / 2);
				players[i].ktsj /= (experts.size() / 2);
				players[i].jxln /= (experts.size() / 2);
				players[i].total = players[i].cgbg + players[i].ktsj + players[i].jxln;
				//cout << players[i].cgbg << " " << players[i].ktsj << " " << players[i].jxln <<" " << players[i].total << endl;
			}
			cout << "开始导出选手报名总表!" << endl;
			ofstream mycout;
			mycout.open("example.txt");
			for (int i = 0; i < players.size(); i++) {
				mycout << players[i].teacherID << "\t" << players[i].name << "\t" << players[i].college << "\t" << players[i].category << "\n";
			}
			mycout.close();
			sort(players.begin(), players.end(), cmp);
			for (int i = 0; i < players.size(); i++) {
				cout << "name = " << players[i].name << "total = " << players[i].total << endl;

			}
			return 0;
		}
	}
	return 0;
}