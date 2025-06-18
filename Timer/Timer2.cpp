#include <iostream>
#include <asio.hpp>
#include <thread>

using namespace std;

void print(const error_code ec)
{
    cout << " Hello World " << endl;
}

int main()
{

    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(15));

    t.async_wait(&print);

    for (int i = 1; i <= 10; i++)
    {
        this_thread::sleep_for(asio::chrono::seconds(1));
        cout << i << endl;
    }
    io.run();

    //jab bhi hum async operation arta hai tab io.run(must provide some work and call) uska wait karta ha pura hona ka 
    //data waha milta hai jaha hum io.run call karta hai


    return 0;
}