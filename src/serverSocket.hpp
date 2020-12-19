#pragma once

#include <boost/asio.hpp>

class ServerSocket
{
public:
    ServerSocket(std::string networkConfigPath);
    ~ServerSocket();
    int send(const unsigned char data[], long bytesToSend);
    int receive(unsigned char dataBuf[], long size);

private:
    boost::asio::io_service ioService_;
    boost::asio::ip::udp::endpoint remoteEndpoint_;
    boost::asio::ip::udp::socket socket_;

    unsigned int maxPacketSize_;
    unsigned short serverPort_;

};
