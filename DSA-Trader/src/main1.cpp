#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "../include/Search.h"
#include "../include/Stack.h"
#include "../include/Leaderboard.h"

using namespace std;
namespace fs = std::filesystem;

struct Holding {
    string stock;
    int quantity;
};

struct ProfitUser {
    string username;
    double profit;
};

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

bool compareProfit(const ProfitUser& a, const ProfitUser& b) {
    return a.profit > b.profit;
}



bool userExists(const string& username) {
    ifstream file("../data/users.csv");
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        size_t comma = line.find(',');
        string user = line.substr(0, comma);
        if (trim(user) == trim(username)) return true;
    }
    return false;
}

bool authenticateUser(const string& username, const string& password) {
    ifstream file("../data/users.csv");
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        size_t comma = line.find(',');
        string user = line.substr(0, comma);
        string pass = line.substr(comma + 1);
        if (trim(user) == trim(username) && trim(pass) == trim(password)) return true;
    }
    return false;
}

void registerUser(const string& username, const string& password) {
    ofstream file("../data/users.csv", ios::app);
    file << username << "," << password << "\n";
    file.close();

    ofstream tfile("../data/" + username + "_transactions.csv");
    tfile << "Type,Stock,Quantity,Price\n";
    tfile.close();

    ofstream pfile("../data/" + username + "_portfolio.csv");
    pfile << "Balance\n1000.0\n";
    pfile.close();
}

// ------------------ Portfolio Persistence ------------------

double loadPortfolio(const string& filename, Holding holdings[], int& count) {
    ifstream file(filename);
    if (!file.is_open()) return 1000.0;

    string line;
    getline(file, line); // "Balance"
    getline(file, line); // value
    double balance = stod(line);
    count = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string stock;
        int qty;
        getline(ss, stock, ',');
        ss >> qty;
        holdings[count++] = {stock, qty};
    }

    return balance;
}

void savePortfolio(const string& filename, double balance, Holding holdings[], int count) {
    ofstream file(filename);
    file << "Balance\n" << balance << "\n";
    for (int i = 0; i < count; i++) {
        file << holdings[i].stock << "," << holdings[i].quantity << "\n";
    }
}

// ------------------ Fetch Price ------------------

double fetchPrice(const string& symbol) {
    string command = "python ../python/fetch_price.py " + symbol;
    int result = system(command.c_str());

    ifstream file("../data/price.csv");
    if (!file.is_open()) {
        cout << "Failed to fetch price.\n";
        return -1;
    }

    string line, sym, priceStr, time;
    getline(file, line); // skip header
    getline(file, line); // data
    stringstream ss(line);
    getline(ss, sym, ',');
    getline(ss, priceStr, ',');
    getline(ss, time, ',');

    cout << "\nReal-time Price for " << sym << " is $" << priceStr << " (as of " << time << ")\n";
    return stod(priceStr);
}

string binarySearchSymbol(const string& name) {
    vector<pair<string, string>> stockMap = {
        {"Apple", "AAPL"},
        {"Tesla", "TSLA"},
        {"Microsoft", "MSFT"},
        {"Amazon", "AMZN"},
        {"Nvidia", "NVDA"},
    };

    for (auto& p : stockMap) {
        if (p.first == name) return p.second;
    }

    return name; // fallback to input
}

// ------------------ Main ------------------

int main() {
    string username, password;
    int choice;

    cout << "1. Login\n2. Register\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (choice == 1) {
        if (!authenticateUser(username, password)) {
            cout << "Invalid credentials.\n";
            return 1;
        }
    } else {
        if (userExists(username)) {
            cout << "User already exists.\n";
            return 1;
        }
        registerUser(username, password);
    }

    string portfolioFile = "../data/" + username + "_portfolio.csv";
    string transactionFile = "../data/" + username + "_transactions.csv";

    Holding holdings[100];
    int count;
    double balance = loadPortfolio(portfolioFile, holdings, count);
    TransactionStack txnHistory;

    while (true) {
        cout << "\n==== MENU ====" << endl;
        cout << "1. Begin Trading" << endl;
        cout << "2. View Transactions" << endl;
        cout << "3. View Portfolio" << endl;
        cout << "4. View Leaderboard" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            while (true) {
                string stock;
                int qty;
                cout << "Enter stock name: ";
                getline(cin, stock);
                cout << "Enter quantity: ";
                cin >> qty;
                cin.ignore();

                string symbol = binarySearchSymbol(stock);
                double price = fetchPrice(symbol);
                double totalCost = qty * price;

                if (totalCost > balance) {
                    cout << "Insufficient balance.\n";
                    break;
                }

                balance -= totalCost;
                bool found = false;
                for (int i = 0; i < count; i++) {
                    if (holdings[i].stock == symbol) {
                        holdings[i].quantity += qty;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    holdings[count++] = {symbol, qty};
                }

                ofstream tf(transactionFile, ios::app);
                tf << "Buy," << symbol << "," << qty << "," << price << "\n";
                tf.close();

                txnHistory.push({true, symbol, qty, price});
                savePortfolio(portfolioFile, balance, holdings, count);

                char cont;
                cout << "Do you want to continue trading? (y/n): ";
                cin >> cont;
                cin.ignore();
                if (cont != 'y' && cont != 'Y') break;
            }
        } else if (choice == 2) {
            txnHistory.display();
        } else if (choice == 3) {
            cout << "\nBalance: $" << balance << endl;
            cout << "Holdings:\n";
            for (int i = 0; i < count; i++) {
                cout << holdings[i].stock << ": " << holdings[i].quantity << " shares\n";
            }
        } else if (choice == 4) {
            showLeaderboard("../data");
        } else {
            break;
        }
    }

    return 0;
}