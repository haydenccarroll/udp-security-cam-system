#pragma once

#include <boost/asio.hpp>

class CameraSocket
{
public:
    CameraSocket(std::string networkConfigPath);
    ~CameraSocket();
    bool establishConnection();
    int send(const unsigned char data[], int bytesToSend);
    int receive(unsigned char data[], int size);

private:
    boost::asio::io_service ioService_;
    boost::asio::ip::udp::resolver resolver_;
    boost::asio::ip::udp::endpoint serverEndpoint_;
    boost::asio::ip::udp::socket socket_;

    std::string serverIP_;
    unsigned short serverPort_;
    unsigned int maxPacketSize_;

};
