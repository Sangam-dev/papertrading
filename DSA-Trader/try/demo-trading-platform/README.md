# Demo Trading Platform

This project is a demo trading platform that allows users to manage their stock transactions, including buying and selling stocks. Each user has their own account with a default balance of $1000 and a CSV file that stores their portfolio and transaction history.

## Features

- User authentication with login and signup functionality.
- Each user has a dedicated CSV file for storing their name, portfolio, and transaction history.
- Transaction management that checks for sufficient balance before allowing buy or sell operations.
- Real-time stock price fetching using a Python script.
- Portfolio management to view current holdings and transaction history.

## Project Structure

```
demo-trading-platform
├── src
│   ├── main.cpp          # Entry point of the application
│   ├── User.cpp          # User class implementation
│   ├── User.h            # User class header
│   ├── Transaction.cpp    # Transaction class implementation
│   ├── Transaction.h      # Transaction class header
│   ├── Portfolio.cpp       # Portfolio class implementation
│   ├── Portfolio.h         # Portfolio class header
│   ├── Stack.cpp          # Transaction stack implementation
│   ├── Stack.h            # Transaction stack header
│   ├── Search.cpp         # Search functionality implementation
│   ├── Search.h           # Search functionality header
│   └── types
│       └── index.h       # Type definitions and constants
├── data
│   ├── stocks.csv        # Stock data for transactions
│   └── users
│       └── [username].csv # User-specific data file
├── python
│   └── fetch_price.py    # Python script for fetching stock prices
├── include
│   ├── User.h            # User class header for external access
│   ├── Transaction.h      # Transaction class header for external access
│   ├── Portfolio.h         # Portfolio class header for external access
│   ├── Stack.h            # Transaction stack header for external access
│   └── Search.h           # Search functionality header for external access
├── README.md              # Project documentation
└── Makefile               # Build instructions
```

## Setup Instructions

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use the provided Makefile to build the project:
   ```
   make
   ```
4. Run the application:
   ```
   ./demo-trading-platform
   ```

## Usage

- Upon running the application, users can sign up or log in.
- Users can view their portfolio, make transactions, and check their balance.
- The application fetches real-time stock prices to facilitate transactions.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.