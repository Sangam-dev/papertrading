#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "../include/Search.h"
#include "../include/Stack.h"

using namespace std;

struct Holding {
    string stock;
    int quantity;
};

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// ------------------ User Management ------------------

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

// ------------------ Main ------------------

int main() {
    string username, password;
    int option;

    cout << "Welcome to DSA-Trader\n";
    cout << "1. Login\n2. Register\nChoose: ";
    cin >> option;
    cin.ignore();

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (option == 1) {
        if (!authenticateUser(username, password)) {
            cout << "Invalid credentials.\n";
            return 0;
        }
    } else if (option == 2) {
        if (userExists(username)) {
            cout << "User already exists. Please login.\n";
            return 0;
        }
        registerUser(username, password);
        cout << "Registration successful.\n";
    } else {
        cout << "Invalid option.\n";
        return 0;
    }

    string tfile = "../data/" + username + "_transactions.csv";
    string pfile = "../data/" + username + "_portfolio.csv";

    Holding holdings[100];
    int holdingsCount;
    double balance = loadPortfolio(pfile, holdings, holdingsCount);

    cout << "\nHello, " << username << "!\n";
    cout << "Current Balance: $" << balance << "\n";
    cout << "Your Holdings:\n";
    if (holdingsCount == 0) cout << "None\n";
    for (int i = 0; i < holdingsCount; i++) {
        cout << holdings[i].stock << ": " << holdings[i].quantity << " shares\n";
    }

    char companies[MAX_ROWS][MAX_COMPANY_LEN];
    char symbols[MAX_ROWS][MAX_SYMBOL_LEN];
    int n = readCSV("../data/stocks1.csv", companies, symbols);
    if (n == -1) return 1;

    TransactionStack ts;

    int choice;
    while (true) {
        cout << "\nMenu:\n1. Begin Trading\n2. Show Transaction History\n3. Show Current Holdings\n4. Exit\nChoose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            bool continueTrading = true;
            while (continueTrading) {
                char query[MAX_COMPANY_LEN];
                cout << "\nEnter company name: ";
                cin.getline(query, MAX_COMPANY_LEN);
                int idx = binarySearchPrefix(query, companies, n);
                if (idx == -1) {
                    cout << "Company not found.\n";
                    continue;
                }

                string symbol = symbols[idx];
                double price = fetchPrice(symbol);
                if (price == -1) continue;

                cout << "Current Balance: $" << balance << "\n";

                char action;
                int qty;
                cout << "Buy (B) or Sell (S)? ";
                cin >> action;
                cout << "Quantity: ";
                cin >> qty;
                cin.ignore();

                auto findHolding = [&](const string& stock) -> int {
                    for (int i = 0; i < holdingsCount; i++) {
                        if (holdings[i].stock == stock) return i;
                    }
                    return -1;
                };

                auto updateHoldings = [&](const string& stock, int qty) {
                    int i = findHolding(stock);
                    if (i == -1 && qty > 0) {
                        holdings[holdingsCount++] = {stock, qty};
                    } else if (i != -1) {
                        holdings[i].quantity += qty;
                        if (holdings[i].quantity <= 0) {
                            for (int j = i; j < holdingsCount - 1; j++)
                                holdings[j] = holdings[j + 1];
                            holdingsCount--;
                        }
                    }
                };

                bool buy = (action == 'B' || action == 'b');
                if (buy) {
                    double cost = price * qty;
                    if (cost > balance) {
                        cout << "Insufficient balance. You have $" << balance << "\n";
                        continue;
                    }
                    balance -= cost;
                    updateHoldings(symbol, qty);
                    cout << "Bought " << qty << " shares. Balance: $" << balance << "\n";
                } else {
                    int own = 0;
                    int i = findHolding(symbol);
                    if (i != -1) own = holdings[i].quantity;
                    if (qty > own) {
                        cout << "You only own " << own << " shares.\n";
                        continue;
                    }
                    balance += price * qty;
                    updateHoldings(symbol, -qty);
                    cout << "Sold " << qty << " shares. Balance: $" << balance << "\n";
                }

                ts.push(Transaction(symbol, qty, price, buy));
                ofstream fout(tfile, ios::app);
                fout << (buy ? "Buy" : "Sell") << "," << symbol << "," << qty << "," << price << "\n";
                cout << "Transaction recorded.\n";

                char choice;
                cout << "Do you want to continue trading? (Y/N): ";
                cin >> choice;
                cin.ignore();
                if (choice != 'Y' && choice != 'y') continueTrading = false;
            }
        } else if (choice == 2) {
            cout << "\nAll Transactions:\n";
            ts.display();
        } else if (choice == 3) {
            cout << "\nCurrent Balance: $" << balance << "\n";
            cout << "Current Holdings:\n";
            if (holdingsCount == 0) cout << "None\n";
            for (int i = 0; i < holdingsCount; i++) {
                cout << holdings[i].stock << ": " << holdings[i].quantity << " shares\n";
            }
        } else {
            break;
        }
    }

    savePortfolio(pfile, balance, holdings, holdingsCount);
    cout << "\nFinal Balance: $" << balance << "\n";
    cout << "Updated Holdings:\n";
    for (int i = 0; i < holdingsCount; i++) {
        cout << holdings[i].stock << ": " << holdings[i].quantity << " shares\n";
    }

    return 0;
}
