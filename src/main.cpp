#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <opencv2/opencv.hpp>

#include "cameraSocket.hpp"
#include "serverSocket.hpp"

#include <fstream>


void Server()
{
  const int frameSize = 307200;

  unsigned char* buffer = new unsigned char[frameSize*2]; // should be frameSize, but segfaults otherwise. 
  ServerSocket server("../config/networkConfig.ini");
  server.receive(buffer, frameSize);
  std::cout << "[Server] Client reached out and established a connection...\n";

  long bytesReceived = 0;
  while (true)
  {
    long spaceLeft = frameSize - bytesReceived;

    bytesReceived += server.receive(buffer+bytesReceived, spaceLeft);
    if (bytesReceived == frameSize)
    {
      std::cout << "Just received another frame\n";
      bytesReceived = 0;


      // display buffer
      cv::Mat frame(480, 640, 16, buffer);
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
        const int CHUNK_SIZE = numElements / 10; // breaks up image into 10 packets

        unsigned char* tempPtr = frame.data;
        int unsentBits = numElements;
        while (unsentBits != 0)
        {
          unsentBits -= cameraSocket.send(tempPtr, CHUNK_SIZE);
          tempPtr += CHUNK_SIZE;
        }

        if( frame.empty() ) break; // end of video stream
          cv::imshow("Client camera", frame);
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