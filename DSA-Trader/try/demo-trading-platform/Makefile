CC = g++
CFLAGS = -Iinclude -std=c++11
SRC = src/main.cpp src/User.cpp src/Transaction.cpp src/Portfolio.cpp src/Stack.cpp src/Search.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = demo-trading-platform

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)