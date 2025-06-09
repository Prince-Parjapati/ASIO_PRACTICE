cmake_minimum_required(VERSION 3.10)

project(Class_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include_directories(${CMAKE_SOURCE_DIR}/include/asio-1.30.2/include/)

find_package(Threads REQUIRED)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include/asio-1.30.2/include/)
target_link_libraries(main PRIVATE Threads::Threads)
