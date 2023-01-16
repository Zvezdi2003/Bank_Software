#ifndef  ENCODINGPASSWORD_USER_SERVICES_H
#define ENCODINGPASSWORD_USER_SERVICES_H

#include <string>
#include <vector>
#include "user-data.h"
#include "global-constants.h"

using namespace std;

string approvedSymbols = "!@#$%^&*";
vector<UserData> users;
bool isLogged = false;
UserData loggedUser;

void loadUsers() {
	
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