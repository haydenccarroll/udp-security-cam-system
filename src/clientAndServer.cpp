// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <string>

using boost::asio::ip::udp;


using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  std::time_t now = std::time(0);
  return std::ctime(&now);
}


void Server()
{
try
  {
    boost::asio::io_service io_service;

    udp::socket socket (io_service, udp::endpoint(udp::v4(),28960));

    while (true)
    {

      // needed so it can establish a connection to client (it now knows clients address and port number)
      char recv[1];
      udp::endpoint remote_endpoint;
      boost::system::error_code error;
      socket.receive_from(boost::asio::buffer(recv), remote_endpoint, 0, error);
      std::cout << "[Server] Received client message: " << recv << '\n';


      if (error)
      {
        throw boost::system::system_error(error);
      }

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

}




int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: (S or C)  <server IP>" << std::endl;
      return 1;
    }
    if (argv[1][0] == 'S')
    {
        Server();
        return 0;
    }

    // creates necessary io service object
    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[2], "28960"); // creates a list of endpoints
    udp::endpoint receiver_endpoint = *resolver.resolve(query); // uses first endpoint


    // create the socket
    udp::socket socket(io_service);
    socket.open(udp::v4()); // opens a socket using ipv4 standard

    char buffWeSend[1] = {'A'};
    socket.send_to(boost::asio::buffer(buffWeSend), receiver_endpoint);

    char bufferWeReceive[128] = {0}; // creates a buffer all intialized to 0 (so there is no garbage)
    udp::endpoint sender_endpoint;

    size_t len = socket.receive_from(boost::asio::buffer(bufferWeReceive), sender_endpoint);

    std::cout << "[Client] Received server message: " << bufferWeReceive << '\n';
    std::cout << "\tServer socket: " << sender_endpoint << '\n';
    std::cout << "\tMessage length: " << len << '\n';

  
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}