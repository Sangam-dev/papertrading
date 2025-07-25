import yfinance as yf
import sys
import csv
from datetime import datetime

symbol = sys.argv[1].upper()
ticker = yf.Ticker(symbol)

try:
    data = ticker.history(period="1d", interval="1m")
    if data.empty:
        raise ValueError("No data found")

    latest = data.iloc[-1]
    price = round(latest['Close'], 2)
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    with open("/home/sangam/programming/dsa/DSA-Trader/data/price.csv", mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Symbol", "Price", "Timestamp"])
        writer.writerow([symbol, price, timestamp])  # <-- Fixed missing closing parenthesis

except Exception as e:
    print("Error fetching stock data:", e)
    sys.exit(1)