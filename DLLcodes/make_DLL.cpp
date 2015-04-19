// dlltry3.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "Windows.h"
#include "extcode.h"
#include "dlltr3.h"
#include "opencv2/opencv.hpp"

using namespace cv;
DLLIMPORT int32_t add(double in1, double in2, double *out)
{

	*out = in1 + in2;
	///
	VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
	////

	return 1;

}
