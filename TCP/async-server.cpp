#include <iostream>
#include <asio.hpp>
#include <string>
#include <array>

using namespace std;
using namespace asio::ip;

class Session : public enable_shared_from_this<Session>
{
private:
    tcp::socket socket_;
    array<char, 128> buf;

    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(asio::buffer(buf), [this, self](error_code ec, size_t len)
                                {
            if(ec == asio::error::eof){
                cout << "[Server] Client disconnected" << endl;
            }
            else if(ec){
                cout << "[Server] " << ec.message() << endl;
            }
            else{
                cout << "[Server] Recieved : " << string(buf.data(), len) << endl;
                do_write(len);
            } });
    }

    void do_write(size_t len)
    {
        shared_ptr<Session> self(shared_from_this());
        socket_.async_write_some(asio::buffer(buf, len), [this, self](error_code ec, size_t len)
                                 {
            if(ec == asio::error::eof){
                cout << "[Server] Client disconnected" << endl;
            }
            else if(ec){
                cout << "[Server] " << ec.message() << endl;
            }
            else{
                do_read();
            } });
    }

public:
    Session(tcp::socket socket) : socket_(move(socket)) {}

    void start()
    {
        do_read();
    }
};

class tcp_server
{
private:
    tcp::acceptor acceptor_;

    void do_connection()
    {
        acceptor_.async_accept([this](error_code ec, tcp::socket socket)
                               { 
            if (!ec)
            {
                cout << "[Server] New client connected" << endl;
                make_shared<Session>(move(socket))->start();
            }
            else
            {
                cerr << "[Server] Accept error: " << ec.message() << endl;
            }
            do_connection(); });
    }

public:
    tcp_server(asio::io_context &io) : acceptor_(io, tcp::endpoint(tcp::v4(), 5500))
    {
        do_connection();
    }
};

int main()
{
    try
    {

        asio::io_context io;
        tcp_server server(io);
        cout << "[Server] is running at port 5500" << endl;
        io.run();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}