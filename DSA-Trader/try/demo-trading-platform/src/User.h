#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    User(const std::string& username, const std::string& password);
    
    bool signup();
    bool login(const std::string& password);
    
    double getBalance() const;
    bool updateBalance(double amount);
    
    void loadUserData();
    void saveUserData() const;

private:
    std::string username;
    std::string password;
    double balance;
    std::vector<std::string> portfolio; // List of stocks in the user's portfolio
    std::vector<std::string> transactionHistory; // List of transactions made by the user
};

#endif // USER_H