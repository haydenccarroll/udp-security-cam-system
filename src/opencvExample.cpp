#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
// using namespace cv;
// int main(int argc, char** argv)
// {
//     VideoCapture cap;
//     // open the default camera, use something different from 0 otherwise;
//     // Check VideoCapture documentation.
//     if(!cap.open(0))
//         return 0;
//     for(;;)
//     {
//           std::vector<char> buffer;
//           Mat frame;
//           cap >> frame;
//           if( frame.empty() ) break; // end of video stream
//           imshow("this is you, smile! :)", frame);
//           if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
//     }
//     // the camera will be closed automatically upon exit
//     // cap.close();
//     return 0;
// }