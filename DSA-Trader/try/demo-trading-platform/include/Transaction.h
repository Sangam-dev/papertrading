class Transaction {
public:
    Transaction();
    Transaction(const std::string& name, int qty, float prc, bool buy);
    void display() const;

    std::string stockName;
    int quantity;
    float price;
    bool isBuy;
};