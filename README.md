# SymTable Link

C++ implementation of a **Symbol Table** using a **Linked List**. It supports various operations such as inserting, removing, replacing, retrieving key-value pairs, and applying functions to all entries.

## Features

- **Insert** a new key-value pair
- **Retrieve** value by key
- **Replace** value for an existing key
- **Remove** a key-value pair
- **Map** a function to all key-value pairs
- Built with **C++** using **Linked List**

## Requirements

Before running the project, ensure that you have the following installed:

- **C++ Compiler** (GCC or Clang)
- **CMake** (to generate the build files)
- **Google Test** (for running unit tests)

For Ubuntu-based systems, you can install the necessary dependencies with:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake libgtest-dev
```

## Installation

### 1. Clone the repository:

```bash
git clone https://github.com/your-username/symTable_link.git
cd symTable_link
```

### 2. Build the project:

Create a build directory:

```bash
mkdir build
cd build
```

Generate the project files using CMake:

```bash
cmake ..
```

Build the project:

```bash
cmake --build ..
```

### 3. Run tests:

After building the project, run the tests with:

```bash
make run_tests
```

This will compile and run the unit tests to ensure everything works as expected.
