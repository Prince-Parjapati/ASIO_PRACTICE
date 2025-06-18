#!/bin/bash

g++ -std=c++17 -Wall -Werror "./async-server.cpp" -o server
g++ -std=c++17 -Wall -Werror "./client.cpp" -o client