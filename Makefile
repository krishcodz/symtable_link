# Makefile for Symbol Table Implementation

# Compiler settings
CXX = g++
CXXFLAGS = -I./include

# Directories
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include

# Source and object files
SYM_TABLE_SRC = $(SRC_DIR)/symtable_link.cpp
SYM_TABLE_OBJ = $(BUILD_DIR)/symtable_link.o
TEST_SRC = $(TEST_DIR)/test_linked.cpp
TEST_OBJ = $(BUILD_DIR)/test_linked.o

# Header files (for dependencies)
HEADERS = $(INCLUDE_DIR)/SymTable.h

# Test executable
TEST_EXEC = $(BUILD_DIR)/test_linked

# Google Test Libraries
GTEST_LIBS = -lgtest -lgtest_main -lgmock -lpthread

# Default target
all: $(TEST_EXEC)

# Build the symbol table object file
$(SYM_TABLE_OBJ): $(SYM_TABLE_SRC) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build the test object file
$(TEST_OBJ): $(TEST_SRC) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link and create test executable
$(TEST_EXEC): $(SYM_TABLE_OBJ) $(TEST_OBJ)
	$(CXX) $^ $(GTEST_LIBS) -o $@

# Clean target
clean:
	@echo "Cleaning up generated files..."
	@rm -f $(BUILD_DIR)/*.o $(TEST_EXEC)
	@rm -rf $(BUILD_DIR)

# Test target
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Declare phony targets
.PHONY: all clean test