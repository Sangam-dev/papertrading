#include "../include/Stack.h"
#include <iostream>
#include <string>

TransactionStack::TransactionStack() {
    top = -1;
}

bool TransactionStack::isEmpty() const {
    return top == -1;
}

bool TransactionStack::isFull() const {
    return top == MAX_SIZE - 1;
}

bool TransactionStack::push(const Transaction& t) {
    if (isFull()) {
        std::cout << "Stack overflow! Cannot add more transactions.\n";
        return false;
    }
    top++;
    stack[top] = t;
    return true;
}

Transaction TransactionStack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty. Cannot peek.");
    }
    return stack[top];
}

void TransactionStack::display() const {
    if (isEmpty()) {
        std::cout << "No transactions to display.\n";
        return;
    }
    std::cout << "Transaction History (Most recent on top):\n";
    for (int i = top; i >= 0; i--) {
        std::cout << (stack[i].isBuy ? "Buy " : "Sell ")
                  << "Stock: " << stack[i].stockName
                  << ", Qty: " << stack[i].quantity
                  << ", Price: $" << stack[i].price << "\n";
    }
}
