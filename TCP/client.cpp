#include <iostream>
#include <asio.hpp>
#include <string>
#include <array>

using namespace std;

int main()
{

    asio::io_context io;

    asio::ip::tcp::resolver resolve(io);

    asio::ip::tcp::socket socket(io);

    asio::connect(socket, resolve.resolve("127.0.0.1", "5500"));

    array<char, 128> buf;

    error_code ec;

    cout << "[Client] Connected to server" << endl;

    while (true)
    {
        string msg;

        getline(cin, msg);

        asio::write(socket, asio::buffer(msg));

        long unsigned int len = socket.read_some(asio::buffer(buf), ec);

        if (ec == asio::error::eof)
        {
            cout << "[Client] Server disconnected";
            break;
        }
        else if (ec)
        {
            cout << "[Client] " << ec.message() << endl;
        }

        cout << "[Client] Server recieved : " << string(buf.data(), len) << endl;
    }

    return 0;
}