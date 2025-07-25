#ifndef SEARCH_H
#define SEARCH_H

const int MAX_ROWS = 1000;
const int MAX_COMPANY_LEN = 100;
const int MAX_SYMBOL_LEN = 10;

// Read CSV into 2D arrays
int readCSV(const char* filename, char companies[][MAX_COMPANY_LEN], char symbols[][MAX_SYMBOL_LEN]);

// Convert string to lowercase
void toLower(char str[]);

// Binary search for prefix match (case-insensitive)
int binarySearchPrefix(const char query[], char companies[][MAX_COMPANY_LEN], int n);

#endif
