#include <iostream>
#include <string>
#include <map>
#include <random>

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

int main() {
	// Map to store the experts, with their account as the key
	std::map<std::string, Expert> experts;

	// Map to store the players, with their teacher ID as the key
	std::map<std::string, Player> players;

	int choice;
	std::cout << "1. Expert entry\n2. Player entry\nEnter your choice: ";
	std::cin >> choice;

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
		experts[expert.account] = expert;
		std::cout << "Expert registered successfully\n";
		std::cout << "Account: " << expert.account << "\n";
	}
	return 0;
}