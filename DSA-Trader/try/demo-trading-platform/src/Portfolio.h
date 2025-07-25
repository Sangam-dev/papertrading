#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>
#include "Transaction.h"

class Portfolio {
public:
    Portfolio();
    void addStock(const std::string& stockName, int quantity, double price);
    void removeStock(const std::string& stockName, int quantity);
    void displayHoldings() const;
    double getTotalValue() const;

private:
    struct Stock {
        std::string name;
        int quantity;
        double price;
    };

    std::vector<Stock> stocks;
};

#endif // PORTFOLIO_H