#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <opencv2/opencv.hpp>

#include "cameraSocket.hpp"
#include "serverSocket.hpp"



void Server()
{
  const int frameSize = 307200;
  cv::VideoCapture cap;

  unsigned char* buffer = new unsigned char[frameSize];
  ServerSocket server("../config/networkConfig.ini");
  server.receive(buffer, frameSize);
  std::cout << "[Server] Client reached out and established a connection...\n";

  int bytesReceived = 0;
  unsigned char* tempPtr = buffer;
  while (true)
  {
    int spaceLeft = frameSize - bytesReceived;
    bytesReceived += server.receive(tempPtr, frameSize-bytesReceived);
    tempPtr += bytesReceived;
    std::cout << bytesReceived << "\n";
    if (bytesReceived == frameSize)
    {
      std::cout << "Just received another frame\n";
      bytesReceived = 0;
      tempPtr = buffer;
      cv::Mat frame(480, 640, 16, buffer);

      cap >> frame;
      cv::imshow("this is a stream of clients stuff", frame);
      cv::waitKey();
    }
  }
}


int openCVClient()
{
    using namespace cv;
    VideoCapture cap;
    CameraSocket cameraSocket("../config/networkConfig.ini");
    cameraSocket.establishConnection();

    if(!cap.open(0))
        return 0;
    while (true)
    {
        Mat frame;
        cap >> frame;
        int numElements = frame.rows*frame.cols;
        const int NUM_BITS_IN_CHUNK = 30720*8;
        const int CHUNK_SIZE = NUM_BITS_IN_CHUNK / CHAR_BIT;

        unsigned char* tempPtr = frame.data;
        int currentSize = numElements;
        while (currentSize != 0)
        {
          cameraSocket.send(tempPtr, CHUNK_SIZE);
          tempPtr += CHUNK_SIZE;
        }
        return 1;

        if( frame.empty() ) break; // end of video stream
        imshow("Client camera", frame);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
      std::cerr << "Usage: (S or C)" << std::endl;
      return EXIT_FAILURE;
    }
    if (argv[1][0] == 'S')
    {
        Server();
        return EXIT_SUCCESS;
    }
    openCVClient();
    return EXIT_FAILURE;
}