#include <iostream>
#include <asio.hpp>

using namespace std;

int main()
{

    asio::io_context io; // all the prorams that uses asio need atleast one I/O execution context

    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    cout << "Hello World" << endl;

    //t.wait wait karta hai timer ko expire hona ka , ya ik blokcing code hai

    return 0;
}