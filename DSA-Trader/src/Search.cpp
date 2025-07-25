#include "../include/Search.h"
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

void toLower(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

int readCSV(const char* filename, char companies[][MAX_COMPANY_LEN], char symbols[][MAX_SYMBOL_LEN]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return -1;
    }

    int count = 0;
    char line[150];
    while (file.getline(line, sizeof(line)) && count < MAX_ROWS) {
        char* name = strtok(line, ",");
        char* symbol = strtok(NULL, ",");

        if (name && symbol) {
            strncpy(companies[count], name, MAX_COMPANY_LEN);
            strncpy(symbols[count], symbol, MAX_SYMBOL_LEN);
            count++;
        }
    }

    file.close();
    return count;
}

bool startsWith(const char* str, const char* prefix) {
    for (int i = 0; prefix[i]; i++) {
        char a = prefix[i];
        char b = str[i];
        if (a >= 'A' && a <= 'Z') a += 32;
        if (b >= 'A' && b <= 'Z') b += 32;
        if (a != b) return false;
    }
    return true;
}

// 🔁 Recursive helper
int binarySearchPrefixRecursive(const char query[], char companies[][MAX_COMPANY_LEN], int low, int high) {
    if (low > high) return -1;

    int mid = (low + high) / 2;

    char qLower[MAX_COMPANY_LEN];
    strcpy(qLower, query);
    toLower(qLower);

    char companyLower[MAX_COMPANY_LEN];
    strcpy(companyLower, companies[mid]);
    toLower(companyLower);

    if (startsWith(companyLower, qLower)) return mid;

    if (strcmp(qLower, companyLower) < 0)
        return binarySearchPrefixRecursive(query, companies, low, mid - 1);
    else
        return binarySearchPrefixRecursive(query, companies, mid + 1, high);
}

// 🔄 Wrapper
int binarySearchPrefix(const char query[], char companies[][MAX_COMPANY_LEN], int n) {
    return binarySearchPrefixRecursive(query, companies, 0, n - 1);
}
