#include "../include/Leaderboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

double computeProfit(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return 0.0;

    std::string line;
    getline(file, line); // skip header
    getline(file, line); // balance
    double currentBalance = std::stod(line);
    return currentBalance - 1000.0;
}

void showLeaderboard(const std::string& userFolder) {
    std::vector<UserProfit> users;

    for (const auto& entry : fs::directory_iterator(userFolder)) {
        std::string file = entry.path().filename().string();
        if (file.find("_portfolio.csv") != std::string::npos) {
            std::string username = file.substr(0, file.find("_portfolio.csv"));
            double profit = computeProfit(entry.path());
            users.push_back({username, profit});
        }
    }

    std::sort(users.begin(), users.end(), [](const UserProfit& a, const UserProfit& b) {
        return a.profit > b.profit;
    });

    std::cout << "\n===== Leaderboard (Profit Ranking) =====\n";
    std::cout << "Username\tProfit\n";
    for (const auto& user : users) {
        std::cout << user.username << "\t\t$" << user.profit << "\n";
    }
}
