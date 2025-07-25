#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

class Search {
public:
    static int binarySearch(const std::vector<std::string>& data, const std::string& target);
    static std::vector<std::string> searchPortfolio(const std::string& username);
};

#endif // SEARCH_H