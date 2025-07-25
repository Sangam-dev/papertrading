#include <iostream>
#include "../include/Search.h"
#include <cstdlib>   
#include <fstream>
#include <sstream>
#include <string>
#include "../include/Stack.h"
using namespace std;

void fetchStockPrice(const string& symbol) {
    string command = "python ../python/fetch_price.py " + symbol;
    int result = system(command.c_str()); 

    if (result != 0) {
        cout << "Failed to fetch stock data.\n";
        return;
    }

    ifstream file("/home/sangam/programming/dsa/DSA-Trader/data/price.csv");
    if (!file.is_open()) {
        cout << "Failed to open price file.\n";
        return;
    }

    string line, sym, price, time;
    getline(file, line); 
    getline(file, line); 

    stringstream ss(line);
    getline(ss, sym, ',');
    getline(ss, price, ',');
    getline(ss, time, ',');

    cout << "\nReal-time Price for " << sym << " is $" << price << " (as of " << time << ")\n";
}

int main() {
    char companies[MAX_ROWS][MAX_COMPANY_LEN];
    char symbols[MAX_ROWS][MAX_SYMBOL_LEN];
    char query[MAX_COMPANY_LEN];

    int n = readCSV("../data/stocks1.csv", companies, symbols);

    if (n == -1) return 1;

    cout << "Enter company name to search: ";
    cin.getline(query, MAX_COMPANY_LEN);

   
    int idx = binarySearchPrefix(query, companies, n);
    if (idx == -1) {
        cout << "Company not found.\n";
        return 1;
    }

    cout << "The company code is " << companies[idx] << endl;
    fetchStockPrice(symbols[idx]);


TransactionStack ts;
char choice;

do {
    cout << "\nEnter company name to search: ";
    cin.getline(query, MAX_COMPANY_LEN);

    int idx = binarySearchPrefix(query, companies, n);
    if (idx == -1) {
        cout << "Company not found.\n";
        continue;
    }

    string symbol = symbols[idx];
    cout << "The company code is " << companies[idx] << endl;

    fetchStockPrice(symbol);

    // Read fetched price
    ifstream file("/home/sangam/programming/dsa/DSA-Trader/data/price.csv");
    if (!file.is_open()) {
        cout << "Failed to open price file.\n";
        continue;
    }

    string line, sym, priceStr, time;
    getline(file, line); // skip header
    getline(file, line); // data
    stringstream ss(line);
    getline(ss, sym, ',');
    getline(ss, priceStr, ',');
    getline(ss, time, ',');

    double price = stod(priceStr);
    int quantity;
    char buyOrSell;

    cout << "Do you want to Buy (B) or Sell (S)? ";
    cin >> buyOrSell;
    cout << "Enter quantity: ";
    cin >> quantity;
    cin.ignore();  // to clear the newline for next getline()

    bool isBuy = (buyOrSell == 'B' || buyOrSell == 'b');

    // Push to stack
    ts.push(Transaction(symbol, quantity, price, isBuy));

    cout << "Transaction recorded.\n";

    cout << "\nDo you want to make another transaction? (Y/N): ";
    cin >> choice;
    cin.ignore(); // clear newline
} while (choice == 'Y' || choice == 'y');

// Display all transactions
cout << "\nAll Transactions:\n";
ts.display();

}
