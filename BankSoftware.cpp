#include <iostream>
#include <string>
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
			cout << "You have " << setprecision(5) << loggedUser.balance << " BGN.Choose one of the following options: " << endl;
			LoggedMenu();
		}
		else {
			GuestMenu();
		}
		cout << "Enter one of the following commands in the menu:" << endl;
		cin >> command;

		if (command == LOGIN_COMMAND) {
			string username, password;
			cout << "Please, enter your username(only latin letters and symbols): ";
			cin >> username;
			cout << "Please, enter your password(only latin letters, numbers and symbols(!@#$%^&*), at least 5 symbols): ";
			cin >> password;
			login(username, password);
			if (!isLogged) {
				cout << "Invalid username or password." << endl;
			}
		}
		else if (command == REGISTER_COMMAND) {
			string username, password;
			cout << "Please, enter your username(only latin letters and symbols): ";
			cin >> username;
			cout << "Please, enter your password(only latin letters, numbers and symbols(!@#$%^&*), at least 5 symbols): ";
			cin >> password;
			cout << create(username, password) << endl;
		}
		else if (command == CANCEL_COMMAND) {
			cancelAccount();
		}
		else if (command == DEPOSIT_COMMAND)
		{
			double amountOFMoney = 0.0;
			cout << "Please, enter how much money you want to deposit: ";
			cin >> amountOFMoney;
			deposit(amountOFMoney);
		}
		else if (command == WITHDRAW_COMMAND)
		{
			double amountWithdraw = 0.0;
			cout << "Please, enter how much money you want to withdraw: ";
			cin >> amountWithdraw;
			withdraw(amountWithdraw);
		}
	}
	saveState();
}

