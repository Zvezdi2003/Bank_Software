#include <iostream>
#include <string>
#include <iomanip>
#include "global-constants.h"
#include "user-services.h"

using namespace std;

void GuestMenu() {
	cout << LOGIN_COMMAND << " - login" << endl;
	cout << REGISTER_COMMAND << " - register" << endl;
	cout << QUIT_COMMAND << " - quit" << endl;
}

void LoggedMenu() {
	cout << CANCEL_COMMAND << " - cancel account" << endl;
	cout << DEPOSIT_COMMAND << " - deposit" << endl;
	cout << LOGIN_COMMAND << " - logout" << endl;
	cout << TRANSFER_COMMAND << " - transfer" << endl;
	cout << WITHDRAW_COMMAND << " - withdraw" << endl;
}



int main() {
	loadUsers();

	string command = "";
	while (command != QUIT_COMMAND) {
		if (isLogged) {
			cout << "You have " << fixed << setprecision(2) << loggedUser.balance << " BGN.Choose one of the following options: " << endl;
			LoggedMenu();
		}
		else {
			GuestMenu();
		}
		cout << "Enter one of the following commands in the menu:" << endl;
		cin >> command;

		if (command == LOGIN_COMMAND) {
			
		}
		else if (command == REGISTER_COMMAND) {
			
		}
		else if (command == CANCEL_COMMAND) {
			
		}
		else if (command == DEPOSIT_COMMAND)
		{
			
		}
		else if (command == TRANSFER_COMMAND)
		{
			
		}
		else if (command == WITHDRAW_COMMAND)
		{
			
		}
	}
	saveState();
}

