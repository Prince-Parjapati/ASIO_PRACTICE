#include<iostream>
#include<array>
#include<string>
#include<asio.hpp>
#include<thread>
#include<chrono>

using namespace std;
using namespace asio::ip;

int main(){


    try{

        asio::io_context io;

        udp::socket socket(io, udp::endpoint(udp::v4(), 12345));

        cout << "[Server] Server is listening at 12345" << endl;

        udp::endpoint sender_endpoint;

        array<char, 128> buf;

        while(true){
            size_t len = socket.receive_from(asio::buffer(buf), sender_endpoint);
            cout << "[Server] Client send : " << string(buf.data(), len) << endl;
            string msg = "Data Recevied...." ;
            socket.send_to(asio::buffer(msg), sender_endpoint);
        }

        //to verify udp
        // while(true){
        //     size_t len = socket.receive_from(asio::buffer(buf), sender_endpoint);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
        //     cout << "[Server] Client send : " << string(buf.data(), len) << endl;
        // }

    }
    catch(exception& e){
        cerr << e.what() << endl;
        return 0;
    }

    return 0;
}