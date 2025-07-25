#include "Search.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> searchStocks(const string& query) {
    vector<string> results;
    ifstream file("../data/stocks.csv");
    if (!file.is_open()) {
        cout << "Failed to open stocks file.\n";
        return results;
    }

    string line;
    while (getline(file, line)) {
        if (line.find(query) != string::npos) {
            results.push_back(line);
        }
    }

    file.close();
    return results;
}

void displaySearchResults(const vector<string>& results) {
    if (results.empty()) {
        cout << "No stocks found matching the search criteria.\n";
        return;
    }

    cout << "Search Results:\n";
    for (const auto& stock : results) {
        cout << stock << endl;
    }
}