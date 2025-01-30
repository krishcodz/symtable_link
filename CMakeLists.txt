# Define project name and language
cmake_minimum_required(VERSION 3.10)
project(SymbolTable CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Add source files
set(SYM_TABLE_SRC ${SRC_DIR}/symtable_link.cpp)
set(TEST_SRC ${TEST_DIR}/test_linked.cpp)

# Add executable target for the test
add_executable(test_linked ${SYM_TABLE_SRC} ${TEST_SRC})

# Google Test (Assuming GoogleTest is installed)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link Google Test libraries
target_link_libraries(test_linked ${GTEST_LIBRARIES} pthread)

# Clean output files
set_target_properties(test_linked PROPERTIES CLEAN_DIRECTORIES "build")

# Add custom target for tests
add_custom_target(run_tests
    COMMAND test_linked
    DEPENDS test_linked
    COMMENT "Running tests"
)

# Custom target for cleaning the build folder
add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning build directory"
)
