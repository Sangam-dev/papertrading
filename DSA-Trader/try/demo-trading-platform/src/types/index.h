#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>

const double DEFAULT_BALANCE = 1000.0;

struct User {
    std::string username;
    std::string password;
    double balance;
    std::vector<std::string> portfolio;
    std::vector<std::string> transactionHistory;
};

#endif // INDEX_H