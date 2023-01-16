#ifndef  ENCODINGPASSWORD_USER_SERVICES_H
#define ENCODINGPASSWORD_USER_SERVICES_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "user-data.h"
#include "global-constants.h"

using namespace std;

string approvedSymbols = "!@#$%^&*";
vector<UserData> users;
bool isLogged = false;
UserData loggedUser;

int numbersAfterComma(string str) {
	bool comma = false;
	int counter = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (comma) {
			counter++;
		}
		if (str[i] == ',' || str[i] == '.') {
			comma = true;
		}
	}
	return  counter;
}

double stringToDouble(string str)
{
	double number = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.' || str[i] == ',') {
			continue;
		}
		number = number * 10 + (str[i] - '0') * 10;
	}
	int digitsAfterComa = numbersAfterComma(str);
	digitsAfterComa++;

	while (digitsAfterComa > 0) {
		number /= 10;
		digitsAfterComa--;
	}

	return number;

}

void loadUsers() {
	std::ifstream file("users.txt");

	if (!file.is_open()) {
		cerr << "Error: unable to open file." << endl;
		return;
	}

	string current;
	getline(file, current, ':');

	while (current != "\n" && !file.eof())
	{

		UserData user;

		user.username = current;

		getline(file, current, ':');
		user.password = current;

		getline(file, current);
		user.balance = stringToDouble(current);

		users.push_back(user);

		getline(file, current, ':');
	}
}

unsigned Hashing(string password)
{
	
}

bool existsByUsername(string username) {
	
}
string intToString(int n)
{
	
}
void login(string username, string password) {
	
}

string create(string username, string password) {

}

void logout() {

}
void cancelAccount() {

}

void deposit(double& amount) {

}

void transfer(string username, double amount) {

}

void withdraw(double amount) {

}
bool saveState() {
	
}

#endif //ENCODINGPASSWORD_USER_SERVICES_H
