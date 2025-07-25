#ifndef TRANSACTION_STACK_H
#define TRANSACTION_STACK_H

#include <string>

const int MAX_SIZE = 100;

struct Transaction {
    std::string stockName;
    int quantity;
    double price;
    bool isBuy;  // true = buy, false = sell

    Transaction() : stockName(""), quantity(0), price(0.0), isBuy(true) {}

    Transaction(const std::string& name, int qty, double p, bool buy)
        : stockName(name), quantity(qty), price(p), isBuy(buy) {}
};

class TransactionStack {
private:
    Transaction stack[MAX_SIZE];
    int top;

public:
    TransactionStack();
    bool push(const Transaction& t);
    Transaction peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void display() const;
};

#endif
