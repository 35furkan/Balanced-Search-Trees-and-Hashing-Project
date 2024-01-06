CC = g++
CFLAGS = -std=c++11

# List your source files
SRC = main.cpp KmerNode.cpp HashTable.cpp 

# The output executable name
EXEC = hw4

# Default target
all: $(EXEC)

# Compile the source files into object files
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Clean the generated files
clean:
	rm -f $(EXEC)
