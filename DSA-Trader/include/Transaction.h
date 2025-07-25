#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string stockName;
    int quantity;
    float price;
    bool isBuy;

    Transaction(); // default constructor
    Transaction(const std::string& name, int qty, float prc, bool buy);

    void display() const;
};

#endif
