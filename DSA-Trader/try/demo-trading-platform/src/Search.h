#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

class Search {
public:
    static std::vector<std::string> searchStocks(const std::string& query);
    static bool stockExists(const std::string& symbol);
};

#endif // SEARCH_H