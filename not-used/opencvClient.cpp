#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "cameraSocket.hpp"
using namespace cv;
// int openCvClientFunct()
// {
//     VideoCapture cap;
//     CameraSocket cameraSocket("../config/networkConfig.ini");
//     cameraSocket.establishConnection();

//     // open the default camera, use something different from 0 otherwise;
//     // Check VideoCapture documentation.
//     if(!cap.open(0))
//         return 0;
//     while (true)
//     {
//         Mat frame;
//         cap >> frame;


//         int num_el = frame.rows*frame.cols;
//         std::string str(frame.data, frame.data + num_el);
//         const int NUM_BITS_IN_CHUNK = 30000;
//         const int CHUNK_SIZE = NUM_BITS_IN_CHUNK / CHAR_BIT;

//         for(std::string::const_iterator iter = str.begin(); iter < str.end(); iter += CHUNK_SIZE)
//         {
//             std::string subStr(iter, iter + CHUNK_SIZE);
//             cameraSocket.send(subStr);
//         }
//         std::cout << "SENT ONE WHOLE FRAME\n";

//         if( frame.empty() ) break; // end of video stream
//         imshow("this is you, smile! :)", frame);
//         if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
//     }
//     // the camera will be closed automatically upon exit
//     // cap.close();
//     return 0;
// }