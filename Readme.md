# Standalone ASIO Network Programming

A simple C++ networking project demonstrating how to set up and use standalone ASIO (Asynchronous I/O) library with CMake.

## Overview

This project demonstrates how to configure and use the standalone version of ASIO C++ library for network programming. ASIO is a cross-platform C++ library for network and low-level I/O programming that provides a consistent asynchronous model.

## Prerequisites

- C++11 or newer compiler
- CMake 3.10 or newer
- The standalone ASIO library (included in this project)
- pthreads library (usually available on Linux systems by default)

## Project Structure

```
Project/
├── CMakeLists.txt
├── include/
│   └── asio-1.30.2/    # Standalone ASIO library
├── src/
│   └── main.cpp        # Main application code
└── build/              # Build directory
```

## Setup Instructions

### 1. Clone or download the repository

```bash
git clone <repository-url>
cd <repository-directory>
```

### 2. Create a CMakeLists.txt file

Create a CMakeLists.txt in your project root with the following content:

```cmake
cmake_minimum_required(VERSION 3.10)
project(AsioNetworking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for ASIO
include_directories(${CMAKE_SOURCE_DIR}/include/asio-1.30.2/include)

# Define ASIO_STANDALONE to use standalone version (not Boost.Asio)
add_definitions(-DASIO_STANDALONE)

# Find pthreads (required by ASIO)
find_package(Threads REQUIRED)

# Add your source files
add_executable(main src/main.cpp)

# Link with required libraries
target_link_libraries(main PRIVATE Threads::Threads)
```

### 3. Write your ASIO code

Here's a basic example similar to your current main.cpp:

```cpp
#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <thread>

int main() {
    asio::io_context io;
    std::cout << "ASIO Version: " << ASIO_VERSION << std::endl;
    
    // Add your networking code here
    
    return 0;
}
```

### 4. Build the project

```bash
mkdir -p build
cd build
cmake ..
make
```

### 5. Run the application

```bash
./main
```

## Important Configuration Notes

1. **ASIO_STANDALONE**: Always define this macro to use ASIO without Boost
2. **Thread Library**: ASIO requires threading support, so link with pthreads on Unix-like systems
3. **Include paths**: Make sure the ASIO headers are correctly set in your include paths

## Example Extensions

You can extend the basic example to:
- Create TCP/UDP servers and clients
- Implement asynchronous networking operations
- Create connection pools
- Implement custom protocols

