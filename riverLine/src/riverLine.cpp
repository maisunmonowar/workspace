//============================================================================
// Name        : River Line.cpp
// Author      : Maisun Monowar, Abdulla Kafi, Raihana Anto, Munir Maruf
// Version     : 1.0
// Copyright   : GPL V.2	
// Description : This program takes an image file and displays edges
//
//Online Repository: github.com/maisunmonowar/workspace
//============================================================================


//Including files necessary to compile
#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

//Using Standard and OpenCV Namespace
using namespace std;
using namespace cv;

//Main function
int main(int argc, char** argv)
{
	//Reading Image file
	Mat img = imread(argv[1]);
	//Checking for errors
	if (img.empty())
	{
		cout << "Can't read image '" << argv[1] << "'\n";
	        return -1;
        }
   //if source is from video. following three lines should be used
    //VideoCapture cap(0); // open the default camera
    //if(!cap.isOpened())  // check if we succeeded
      //  return -1;

    Mat edges;
    //creating display windows
    namedWindow("original",WINDOW_AUTOSIZE);
    namedWindow("first",WINDOW_AUTOSIZE);
    namedWindow("result",WINDOW_AUTOSIZE);
  
  
   //if source is video, use loop
    //for(;;)
    //{
       // Mat frame;
        //cap >> frame; // get a new frame from camera
        cvtColor(img, edges, CV_BGR2GRAY);
        imshow("original", edges);
        GaussianBlur(edges, edges, Size(9,9), 10, 10);
        GaussianBlur(edges, edges, Size(9,9), 10, 10);
        //imshow("second", edges);//debug purpose
        Canny(edges, edges, 10, 30, 3);
        imshow("result", edges);
        imwrite("result.jpg", edges);

    //    if(waitKey(30) >= 0) break;
    //}
    // the camera will be deinitialized automatically in VideoCapture destructor
    waitKey(0);
    //Program finished. Return an Integar
    return 1;
}
