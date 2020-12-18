#include "serverSocket.hpp"

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <string>
#include <iostream>

ServerSocket::ServerSocket(std::string networkConfigPath) : 
ioService_(),
socket_(ioService_)
{
    using namespace boost::asio::ip;

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(networkConfigPath, pt);
    serverPort_ = pt.get<unsigned short>("serverInfo.portNumber");
    maxPacketSize_ = pt.get<unsigned int>("packetInfo.maxPacketSize");

    socket_ = udp::socket(ioService_, udp::endpoint(udp::v4(), serverPort_));

}

ServerSocket::~ServerSocket()
{
}



int ServerSocket::send(const unsigned char data[], int bytesToSend)
{

    return socket_.send_to(boost::asio::buffer(data, bytesToSend), remoteEndpoint_);
}

int ServerSocket::receive(unsigned char dataBuf[], int size)
{
    return socket_.receive_from(boost::asio::buffer(dataBuf, size), remoteEndpoint_);
}