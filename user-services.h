#ifndef  ENCODINGPASSWORD_USER_SERVICES_H
#define ENCODINGPASSWORD_USER_SERVICES_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "user-data.h"
#include "global-constants.h"
#include <iomanip>

using namespace std;

string approvedSymbols = "!@#$%^&*";
vector<UserData> users;
bool isLogged = false;
UserData loggedUser;


double stringToDouble(string str)
{
	double result = 0.0;
	int index = 0;
	for (int i = 0; i != '\0'; i++)
	{
		if (str[i] == '.' || str[i] == ',')
		{
			index = i;
			break;
		}

		result *= 10;
		result += (double)(str[i] - '0');
	}
	int power = 1;
	for (int i = index + 1; i != '\0'; i++)
	{
		result += (double)((str[i] - '0') / pow(10, power));
		power++;
	}
	return result;

}
void loadUsers() {
	std::ifstream file("users.txt");

	if (!file.is_open()) {
		cerr << "Error: unable to open file." << endl;
		return;
	}

	string current;
	while (!file.eof())
	{
		getline(file, current, ':');
		UserData user;

		user.username = current;

		getline(file, current, ':');
		user.password = current;

		getline(file, current);
		user.balance = stringToDouble(current);

		users.push_back(user);
	}
}
bool validateUsername(string name) {
	int index = 0;
	while (name[index++] != '\0')
	{
		if (name[index] < 32 && name[index] > 126)
		{
			return false;
		}
		if (name[index] >= '0' && name[index] <= '9')
		{
			return false;
		}
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

bool existsByUsername(string username) {
	for (UserData& user : users) {
		if (user.username == username) {
			return true;
		}
	}
	return false;
}
string intToString(int n)
{
	string str = to_string(n);
	return str;
}
void login(string username, string password) {
	unsigned hashP = Hashing(password);
	for (UserData& user : users) {
		if (user.username == username && user.password == intToString(hashP)) {
			isLogged = true;
			loggedUser = user;
		}
	}
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
	}
	logout();
}

void deposit(double& amount) {

	if (amount > 0)
	{
		loggedUser.balance += amount;
	}
	else
	{
		cout << "Invalid amount" << endl;
		return;
	}

}

void transfer(string username, double amount) {
	if (amount > 0 && amount <= 10000 && loggedUser.balance >= amount)
	{
		cout << "Please enter the right name of the account to which you want to transfer: ";
		string nameSecond = "";
		cin >> nameSecond;
		if (existsByUsername(nameSecond))
		{
			loggedUser.balance -= amount;
			vector<UserData>::iterator iter;
			for (iter = users.begin(); iter != users.end(); iter++) {
				if ((*iter).username == loggedUser.username) {

				}
			}
		}
	}
}

void withdraw(double amount) {
	if (loggedUser.balance >= amount)
	{
		if (amount > 0 && amount <= 10000)
		{
			loggedUser.balance -= amount;
		}
	}
	else
	{
		cout << "Invalid amount" << endl;
		return;
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