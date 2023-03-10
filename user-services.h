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

	bool isNegative = false;
	if (str[0] == '-') {
		isNegative = true;
	}
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.' || str[i] == ',') {
			continue;
		}
		if (str[i] != '-') {
			number = number * 10 + (str[i] - '0') * 10;
		}
	}
	int digitsAfterComma = numbersAfterComma(str);
	digitsAfterComma++;

	while (digitsAfterComma > 0) {
		number /= 10;
		digitsAfterComma--;
	}
	
	if (isNegative) {
		return -number;
	}
	
	return number;
}

void loadUsers() {
	std::ifstream file("users.txt");

	if (!file.is_open()) {
		cerr << "Error: unable to open file." << endl;
		return;
	}

	string currentData;
	getline(file, currentData, ':');

	while (currentData != "\n" && !file.eof())
	{

		UserData user;

		user.username = currentData;

		getline(file, currentData, ':');
		user.password = currentData;

		getline(file, current);
		user.balance = stringToDouble(currentData);

		users.push_back(user);

		getline(file, currentData, ':');
	}
}

bool validateUsername(string name) {
	int index = 0;
	while (name[index] != '\0')
	{
		if (name[index] < 32 && name[index] > 126)
		{
			return false;
		}
		if (name[index] >= '0' && name[index] <= '9')
		{
			return false;
		}
		index++;
	}
	return true;
}
bool isSmallLetter(char symbol) {
	return (symbol >= 97 && symbol <= 122);
}
bool isBigLetter(char symbol) {
	return (symbol >= 65 && symbol <= 90);
}
bool isDigit(char number) {
	return number >= 48 && number <= 57;
}
bool isApprovedSymbol(char symbol) {
	int index = 0;
	while (approvedSymbols[index] != '\0')
	{
		if (approvedSymbols[index] == symbol)
		{
			return true;
		}
		index++;
	}
	return false;
}

bool isSmallLetter(char symbol) {
	return (symbol >= 97 && symbol <= 122);
}

bool isBigLetter(char symbol) {
	return (symbol >= 65 && symbol <= 90);
}

bool isDigit(char number) {
	return number >= 48 && number <= 57;
}

bool isApprovedSymbol(char symbol) {
	int index = 0;
	while (approvedSymbols[index] != '\0')
	{
		if (approvedSymbols[index] == symbol)
		{
			return true;
		}
		index++;
	}
	return false;
}

bool validatePassword(string pass) {
	int index = 0;
	int countSmallLet = 0;
	int countBigLet = 0;
	int countSymbols = 0;
	int countDigits = 0;
	while (pass[index] != '\0')
	{
		if (isBigLetter(pass[index])) {
			countBigLet++;
		}
		else if (isSmallLetter(pass[index])) {
			countSmallLet++;
		}
		else if (isApprovedSymbol(pass[index])) {
			countSymbols++;
		}
		else if (isDigit(pass[index])) {
			countDigits++;
		}
		else {
			return false;
		}
		index++;
	}
	return index > 4 && countSmallLet > 0 && countBigLet > 0 && countSymbols > 0 && countDigits > 0;
}

unsigned Hashing(string password)
{
	size_t hash = std::hash<std::string>{}(password);
	return hash;
}

string intToString(int n)
{
	string str = to_string(n);
	return str;
}

void login(string username, string password) {
	unsigned hashP = Hashing(password);
	string hashedPassword = intToString(hashP);
	for (UserData& user : users)
	{
		if (user.username == username && user.password == hashedPassword)
		{
			isLogged = true;
			loggedUser = user;
			break;
		}
	}
}

bool existsByUsername(string username) {
	for (UserData& user : users) {
		if (user.username == username) {
			return true;
		}
	}
	return false;
}
string create(string username, string password) {
	if (!validateUsername(username)) {
		return "Invalid username.";
	}
	if (!validatePassword(password)) {
		return "Invalid password.";
	}
	if (existsByUsername(username)) {
		return "User with the same email already exists.";
	}
	unsigned hashP = Hashing(password);
	string hashedPassword = intToString(hashP);
	UserData user = { username, hashedPassword, 0 };
	users.push_back(user);

	isLogged = true;
	loggedUser = user;
	return REGISTERED_SUCCESSFULLY_MESSAGE;
}

void logout() {
	loggedUser = { "", "", 0 };
	isLogged = false;
}
void cancelAccount() {
	string password;
	cout << "Enter your password: ";
	cin >> password;
	if (isLogged && loggedUser.balance == 0)
	{
		vector<UserData>::iterator iter;
		for (iter = users.begin(); iter != users.end(); iter++) {
			if ((*iter).username == loggedUser.username) {
				users.erase(iter);
				break;
			}
		}
		cout << CANCELED_SUCCESSFULLY_MESSAGE << endl;
	}
	if (loggedUser.balance != 0)
	{
		cout << "You need to withdraw your money before canceling your account." << endl;
	}
	logout();
}

void deposit(double& amount) {
	for (auto& x : users) {
		if (x.username == loggedUser.username) {
			if (amount > 0)
			{
				loggedUser.balance += amount;
				x.balance += amount;
			}
			else
			{
				cout << "Invalid amount" << endl;
				return;
			}
			return;
		}
	}
}

void transfer(string username, double amount) {
	for (auto& x : users) {
		if (username == x.username) {
			if (amount > 0 && abs(amount - 10000) >= 0 && abs(loggedUser.balance - amount) >= 0)
			{
				loggedUser.balance -= amount;

				if (!(10000 + loggedUser.balance >= 0)) {
					cout << "The overdraft has reached its limit of 10000!" << '\n';
					loggedUser.balance = -10000;

					for (auto& y : users) {
						if (y.username == loggedUser.username) {
							y.balance = loggedUser.balance;
							break;
						}
					}

					return;
				}

				x.balance += amount;
				cout << "The transfer is made successfully!" << '\n';
				return;
			}
		}
	}
	cout << "User not found" << '\n';
}

void withdraw(double amount) {
	for (auto& x : users) {
		if (x.username == loggedUser.username) {
			if (abs(loggedUser.balance - amount) >= DBL_EPSILON)
			{
				loggedUser.balance -= amount;

				if (!(10000 + loggedUser.balance >= DBL_EPSILON)) {
					cout << "The overdraft has reached its limit of 10000!" << '\n';
					loggedUser.balance = -10000;

					for (auto& y : users) {
						if (y.username == loggedUser.username) {
							y.balance = loggedUser.balance;
							break;
						}
					}
					return;
				}
				x.balance -= amount;
			}
			else
			{
				cout << "Invalid withdraw amount" << endl;
				return;
			}
		}
	}
}

bool saveState() {
	ofstream deleteData("users.txt");

		if (!deleteData.is_open()) {
			cout << "File did not open!" << '\n';
			return false;
		}

		deleteData << "";

		deleteData.close();

		ofstream writeToFile("users.txt", ios::app);

		for (auto& x : users) {
			writeToFile << x.username << ':' << x.password << ':' << x.balance << '\n';
		}

		writeToFile.close();
}

#endif //ENCODINGPASSWORD_USER_SERVICES_H
