# Makefile for POSIX Shell Project

CXX = g++
CXXFLAGS = -Wall -g

# Source files
SRC = src/main.cpp src/shell.cpp src/builtins.cpp src/io_redirection.cpp

# Output binary
TARGET = shell

# Compilation rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule
clean:
	rm -f $(TARGET)