#include "Portfolio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Portfolio::Portfolio() {
    // Initialize an empty portfolio
}

void Portfolio::addStock(const std::string& stockName, int quantity, double price) {
    holdings.push_back({stockName, quantity, price});
}

void Portfolio::removeStock(const std::string& stockName, int quantity) {
    for (auto it = holdings.begin(); it != holdings.end(); ++it) {
        if (it->stockName == stockName) {
            if (it->quantity >= quantity) {
                it->quantity -= quantity;
                if (it->quantity == 0) {
                    holdings.erase(it);
                }
            } else {
                std::cout << "Insufficient quantity to remove.\n";
            }
            return;
        }
    }
    std::cout << "Stock not found in portfolio.\n";
}

void Portfolio::display() const {
    if (holdings.empty()) {
        std::cout << "No stocks in portfolio.\n";
        return;
    }
    std::cout << "Current Portfolio:\n";
    for (const auto& stock : holdings) {
        std::cout << "Stock: " << stock.stockName
                  << ", Qty: " << stock.quantity
                  << ", Price: $" << stock.price << "\n";
    }
}

void Portfolio::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for saving portfolio.\n";
        return;
    }
    for (const auto& stock : holdings) {
        file << stock.stockName << "," << stock.quantity << "," << stock.price << "\n";
    }
    file.close();
}

void Portfolio::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for loading portfolio.\n";
        return;
    }
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string stockName;
        int quantity;
        double price;
        getline(ss, stockName, ',');
        ss >> quantity;
        ss.ignore(); // Ignore the comma
        ss >> price;
        addStock(stockName, quantity, price);
    }
    file.close();
}