#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string stockName;
    int quantity;
    double price;
    bool isBuy;

    Transaction();
    Transaction(const std::string& name, int qty, double prc, bool buy);
    void display() const;
};

#endif // TRANSACTION_H