#include <functional>
#include <iostream>
#include <asio.hpp>

using namespace std;

void print(const asio::error_code& ec, asio::steady_timer* t, int* count) {
    if (*count < 5) {
        cout << *count << endl;
        ++(*count);
        t->expires_at(t->expiry() + asio::chrono::seconds(1));
        t->async_wait(bind(print, std::placeholders::_1, t, count));
    }
}

int main() {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    int count = 0;

    t.async_wait(bind(print, std::placeholders::_1, &t, &count));

    io.run();  

    return 0;
}
