# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -Werror -O3

# Source files
SRCS = main.cpp InputOutputProcessor.cpp Trie.cpp Algorithm.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = output/run

# Valgrind command
VALGRIND = valgrind

# Valgrind flags
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

# Build rule
all: $(TARGET) clean_o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run the executable with Valgrind
valgrind: $(TARGET)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET)

# Clean o files
clean_o:
	rm -f $(OBJS)

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean valgrind
