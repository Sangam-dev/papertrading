#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

User::User() : balance(1000.0) {}

bool User::signup(const std::string& username, const std::string& password) {
    std::ofstream userFile("data/users/" + username + ".csv");
    if (!userFile.is_open()) {
        std::cout << "Failed to create user file.\n";
        return false;
    }
    userFile << username << "," << password << "," << balance << "\n";
    userFile.close();
    return true;
}

bool User::login(const std::string& username, const std::string& password) {
    std::ifstream userFile("data/users/" + username + ".csv");
    if (!userFile.is_open()) {
        std::cout << "User not found.\n";
        return false;
    }

    std::string line;
    getline(userFile, line);
    std::stringstream ss(line);
    std::string fileUsername, filePassword;
    ss >> fileUsername;
    getline(ss, filePassword, ','); // Skip to password
    double fileBalance;
    ss >> fileBalance;

    if (filePassword == password) {
        balance = fileBalance;
        userFile.close();
        return true;
    } else {
        std::cout << "Incorrect password.\n";
        userFile.close();
        return false;
    }
}

double User::getBalance() const {
    return balance;
}

void User::updateBalance(double amount) {
    balance += amount;
    std::ofstream userFile("data/users/" + username + ".csv", std::ios::trunc);
    userFile << username << "," << password << "," << balance << "\n";
    userFile.close();
}

void User::setUsername(const std::string& name) {
    username = name;
}

void User::setPassword(const std::string& pass) {
    password = pass;
}