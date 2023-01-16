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
	
}
void login(string username, string password) {
	
}

bool existsByUsername(string username) {
	
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
