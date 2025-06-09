#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <thread>

int main() {
    asio::io_context io;
    std::cout << "ASIO Version: " << ASIO_VERSION << std::endl;
    return 0;
}
