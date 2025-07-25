#ifndef STACK_H
#define STACK_H

#include "Transaction.h"

const int MAX_SIZE = 100;

class TransactionStack {
private:
    Transaction stack[MAX_SIZE];
    int top;

public:
    TransactionStack();
    bool isEmpty() const;
    bool isFull() const;
    bool push(const Transaction& t);
    Transaction peek() const;
    void display() const;
};

#endif // STACK_H