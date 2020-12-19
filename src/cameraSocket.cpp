#include "cameraSocket.hpp"

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <string>
CameraSocket::CameraSocket(std::string networkConfigPath) : 
ioService_(),
resolver_(ioService_),
socket_(ioService_)
{
    using namespace boost::asio::ip;

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(networkConfigPath, pt);
    serverIP_ = pt.get<std::string>("serverInfo.ipAddress");
    serverPort_ = pt.get<unsigned short>("serverInfo.portNumber");
    maxPacketSize_ = pt.get<unsigned int>("packetInfo.maxPacketSize");

    udp::resolver::query query(udp::v4(), serverIP_, std::to_string(serverPort_));
    serverEndpoint_ = udp::endpoint(*resolver_.resolve(query));

    socket_.open(udp::v4());
}

CameraSocket::~CameraSocket()
{
}


bool CameraSocket::establishConnection()
{
    char buffToSend[1];
    socket_.send_to(boost::asio::buffer(buffToSend), serverEndpoint_);
    return 1;
}


int CameraSocket::send(const unsigned char data[], long bytesToSend)
{

    return socket_.send_to(boost::asio::buffer(data, bytesToSend), serverEndpoint_);
}

int CameraSocket::receive(unsigned char dataBuf[], long size)
{
    return socket_.receive_from(boost::asio::buffer(dataBuf, size), serverEndpoint_);
}
