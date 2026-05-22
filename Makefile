# Variables
CC = g++
# CFLAGS = -fsanitize=address --debug -lm -Wall -Wextra -O2 # Compilation flags
CFLAGS = -std=c++20 -lm -Wconversion -Wall -Wextra -Ofast # Compilation flags
SRCS = $(shell find . -name "*.cpp")  # Find all .c files
OBJS = $(SRCS:.cpp=) # Replace .c extension with no extension for executables
TESTS = $(shell find . -name "test_*.cpp")  # Automatically find test source files

# Generate test executable names by removing 'test_' prefix and the directory structure
TEST_EXES = $(patsubst test_%.cpp, %, $(TESTS))

# Default target to build all executables
all: $(OBJS)

# Rule to compile each .c file into its own executable
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Target to build all test executables
%: test_%.cpp $(OBJS)
	$(CC) $(CFLAGS) -o $@ $< -lcriterion

# Target to run all tests
test: $(TEST_EXES)
	@for exe in $(TEST_EXES); do \
		echo "Running $$exe"; \
		./$$exe; \
	done

# Clean target to remove executables
clean:
	find . -type f -perm /111 -exec rm -f {} +
