#include <iostream>
#include <array>
#include <string>
#include <asio.hpp>

using namespace std;
using namespace asio::ip;

int main()
{

    try
    {

        asio::io_context io;
        udp::resolver resolve(io);
        udp::endpoint recv_endpoint = *resolve.resolve(udp::v4(), "127.0.0.1", "12345").begin();
        udp::socket socket(io);

        socket.open(udp::v4());

        while(true){
        string msg ;
        array<char, 128> buf;
        cout << "[Client] Enter msg : " ;
        getline(cin, msg);
        socket.send_to(asio::buffer(msg), recv_endpoint);
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(asio::buffer(buf), sender_endpoint);
        cout << "[Clinet] Server send : " << string(buf.data(), len) << endl;

        }

        // to verify udp
        // int j = 0;
        // while(j++ < 10)
        // for (int i = 0; i < 10; ++i)
        // {
        //     std::string msg = "Packet " + std::to_string(j) + std::to_string(i);
        //     socket.send_to(asio::buffer(msg), recv_endpoint);
        // }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}