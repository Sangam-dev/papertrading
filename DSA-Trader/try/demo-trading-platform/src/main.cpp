#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "User.h"
#include "Transaction.h"
#include "Portfolio.h"
#include "Stack.h"

using namespace std;

void displayMenu() {
    cout << "1. Sign Up\n";
    cout << "2. Log In\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    User currentUser;
    string username, password;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
            case 1: // Sign Up
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (currentUser.signup(username, password)) {
                    cout << "Sign up successful!\n";
                } else {
                    cout << "Sign up failed. Username may already exist.\n";
                }
                break;

            case 2: // Log In
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (currentUser.login(username, password)) {
                    cout << "Login successful!\n";
                    // Initialize user data and allow transactions
                    double balance = 1000.0; // Default balance
                    TransactionStack ts;
                    char transactionChoice;

                    do {
                        cout << "Do you want to Buy (B) or Sell (S)? ";
                        cin >> transactionChoice;
                        cin.ignore(); // clear newline

                        string stockName;
                        int quantity;
                        double price;

                        cout << "Enter stock name: ";
                        getline(cin, stockName);
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        cout << "Enter price: ";
                        cin >> price;

                        if (transactionChoice == 'B' || transactionChoice == 'b') {
                            if (balance >= price * quantity) {
                                balance -= price * quantity;
                                ts.push(Transaction(stockName, quantity, price, true));
                                cout << "Transaction recorded: Bought " << quantity << " of " << stockName << "\n";
                            } else {
                                cout << "Insufficient balance for this transaction.\n";
                            }
                        } else if (transactionChoice == 'S' || transactionChoice == 's') {
                            balance += price * quantity;
                            ts.push(Transaction(stockName, quantity, price, false));
                            cout << "Transaction recorded: Sold " << quantity << " of " << stockName << "\n";
                        }

                        cout << "Current balance: $" << balance << "\n";
                        cout << "Do you want to make another transaction? (Y/N): ";
                        cin >> transactionChoice;
                        cin.ignore(); // clear newline
                    } while (transactionChoice == 'Y' || transactionChoice == 'y');

                    // Display all transactions
                    ts.display();
                } else {
                    cout << "Login failed. Please check your credentials.\n";
                }
                break;

            case 3: // Exit
                cout << "Exiting the application.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}