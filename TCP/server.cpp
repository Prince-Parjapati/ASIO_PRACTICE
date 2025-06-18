#include <iostream>
#include <asio.hpp>
#include <array>

// for multiple client
#include <thread>
#include <memory>

using namespace std;

void handleClient(shared_ptr<asio::ip::tcp::socket> socket)
{
    try
    {
        array<char, 128> buf;
        error_code ec;
        while (true)
        {
            size_t len = socket->read_some(asio::buffer(buf), ec);
            if (ec == asio::error::eof)
            {
                cout << "[Server] Client disconnected..." << endl;
                return;
            }
            else if (ec)
            {
                cout << "[Server] " << ec.message() << endl;
                return;
            }
            cout << "[Server] " << string(buf.data(), len) << endl;

            socket->write_some(asio::buffer(buf, len), ec);
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return;
    }
}

int main()
{

    asio::io_context io;
    asio::ip::tcp::acceptor acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9874));

    // for single client
    //  while (true)
    //  {
    //      asio::ip::tcp::socket socket(io);
    //      acceptor.accept(socket);
    //      cout << "[Server] " << "New Client Connected" << endl;
    //      error_code ec;
    //      while (true)
    //      {
    //          array<char, 128> buf;
    //          size_t len = socket.read_some(asio::buffer(buf), ec);
    //          if(ec == asio::error::eof){
    //              cout << "[Server] Client disconnected" << endl;
    //              break;
    //          }
    //          else if (ec)
    //          {
    //              cerr << "[Server] " << ec.message() << endl;
    //              return 1;
    //          }
    //          cout << "[Server] " << string(buf.data(), len) << endl;
    //          socket.write_some(asio::buffer(buf, len), ec);
    //      }
    //  }

    // for multiple client

    while (true)
    {
        auto socket = make_shared<asio::ip::tcp::socket>(io);
        acceptor.accept(*socket);
        cout << "[Server] New Client Connected" << endl;

        thread(handleClient, socket).detach();
    }

    return 0;
}

