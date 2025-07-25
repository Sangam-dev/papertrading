#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>

struct UserProfit {
    std::string username;
    double profit;
};

void showLeaderboard(const std::string& userFolder);

#endif
