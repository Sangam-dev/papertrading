class User {
public:
    User(const std::string& username, const std::string& password);
    bool signup();
    bool login();
    double getBalance() const;
    void updateBalance(double amount);
    void saveToFile() const;
    void loadFromFile();

private:
    std::string username;
    std::string password;
    double balance;
    std::string userFilePath;
};