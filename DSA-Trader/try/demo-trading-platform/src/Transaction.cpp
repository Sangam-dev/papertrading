#include "../include/Transaction.h"
#include <iostream>

Transaction::Transaction() {
    stockName = "";
    quantity = 0;
    price = 0.0;
    isBuy = true;
}

Transaction::Transaction(const std::string& name, int qty, float prc, bool buy) {
    stockName = name;
    quantity = qty;
    price = prc;
    isBuy = buy;
}

void Transaction::display() const {
    std::cout << (isBuy ? "Buy " : "Sell ")
              << "Stock: " << stockName
              << ", Qty: " << quantity
              << ", Price: $" << price << std::endl;
}