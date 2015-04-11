//============================================================================
// Name        : CameraTest.cpp
// Author      : Maisun Monowar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread(argv[1]);
	            if (img.empty())
	            {
	                cout << "Can't read image '" << argv[1] << "'\n";
	                return -1;
	            }
    //VideoCapture cap(0); // open the default camera
    //if(!cap.isOpened())  // check if we succeeded
      //  return -1;

    Mat edges;
    namedWindow("original",WINDOW_AUTOSIZE);
    namedWindow("first",WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE
    namedWindow("second",WINDOW_AUTOSIZE);
    for(;;)
    {
       // Mat frame;
        //cap >> frame; // get a new frame from camera
        cvtColor(img, edges, CV_BGR2GRAY);
        imshow("original", edges);
        GaussianBlur(edges, edges, Size(9,9), 10, 10);

        GaussianBlur(edges, edges, Size(9,9), 10, 10);
        imshow("second", edges);
        Canny(edges, edges, 10, 30, 3);
        imshow("first", edges);

        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}