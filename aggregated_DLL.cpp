/*
Name		: aggregated_DLL.cpp
Author      	: Maisun Monowar, Abdulla Kafi, Raihana Antara, Munir Maruf
Version     	: 02
Copyright   	: GPL V.2
Description 	: This is a code for a DLL file which is to be called by 
		LabView GUI

Online Repo	:github.com/maisunmonowar/workspace
*/


//Including files in order to compile the program correctly

#include "stdafx.h"
#include "Windows.h"
#include "extcode.h"
#include "dlltr3.h" 	//Name of our custom made header file. To be changed as necessary
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stringapiset.h>
#include <winstring.h>
#include <xstring>
#include <mshtml.h>
#include <atlbase.h>
#include <comdef.h>
#include "opencv2/opencv.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


//Using standard and OpenCV namespace
using namespace std;
using namespace cv;

//defining 'green'
#define green_h_h 80
#define green_h_l 45
#define green_s_h 255
#define green_s_l 30
#define green_v_h 200
#define green_v_l 30

#define healthy_h_h 65
#define healthy_h_l 55
#define healthy_s_h 255
#define healthy_s_l 30
#define healthy_v_h 200
#define healthy_v_l 30

//function for Health Estimate
DLLIMPORT int32_t healthEstimate(double *g_percent, double *h_g_percent)
{
	//Declaring Local Variables
	Mat img_hsv, imgThresholded, healthyThreshold;
	int total_pixel = 0;
	int total_green = 0;
	int healthy_green = 0;
	float percentage_green = 0;
	float percentage_healthy_green ;
	// open the default camera
	VideoCapture cap(0); 
	// check if succeeded
	if(!cap.isOpened())  
		return -1;
	Mat edges;
	Mat image;
	// get a new frame from camera
	cap >> image; 
	total_pixel = image.total();
	cvtColor(image, img_hsv, COLOR_BGR2HSV);
	inRange(img_hsv, Scalar(green_h_l, green_s_l, green_v_l), Scalar(green_h_h, green_s_h, green_v_h), imgThresholded); //Threshold the image
	inRange(img_hsv, Scalar(healthy_h_l, healthy_s_l, healthy_v_l), Scalar(healthy_h_h, healthy_s_h, healthy_v_h), healthyThreshold);
	//Following block of code is credited to
	//http://stackoverflow.com/questions/7899108/opencv-get-pixel-channel-value-from-mat-image
	for(int i = 0; i < img_hsv.rows; i++)
	{
		for(int j = 0; j < img_hsv.cols; j++)
		{
			Vec3b hsvPixel = img_hsv.at<Vec3b>(i, j);
			// Calculation with BGR values...
			if (hsvPixel.val[1] > green_s_l)
			{
				if (hsvPixel.val[2]>green_v_l && hsvPixel.val[2]<green_v_h)
				{
					if (hsvPixel.val[0]>green_h_l && hsvPixel.val[0]<green_h_h)
					{
						//This pixel is a "Green" pixel
						total_green++;
						//Searching for "Healthy Green" pixel
						if (hsvPixel.val[1] > healthy_s_l)
						{
							if (hsvPixel.val[2]>healthy_v_l && hsvPixel.val[2]<healthy_v_h)
							{
								if (hsvPixel.val[0]>healthy_h_l && hsvPixel.val[0]<healthy_h_h)
								{
									//This pixel is "Healthy Green"
									healthy_green++;
								}
							}
						}
					}
				}
			}
		}
	}

	//Calculating Percentage values
	percentage_green = total_green * 100.0 / total_pixel;
	percentage_healthy_green = healthy_green * 100.0/ total_green ;
	//Passing the values to LavView interface
	*g_percent = percentage_green ;
	*h_g_percent = percentage_healthy_green ;
	// the camera will be deinitialized automatically in VideoCapture destructor
	//Termination of the function
	return 1;
}

//Function of Super Resolution Map

DLLIMPORT int32_t spiltAndStitch(char pString[] )
{
	//Declaring Variables
	vector<Mat> imgs;
	string result_name = "result.jpg";
	struct stat info;
	// open the video file for reading
	VideoCapture cap(pString); 
	// if not success, exit program
	if ( !cap.isOpened() )  
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}
	
	//Offsetting the video if necessary
	//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

	//get the frames per seconds of the video
	double fps = cap.get(CV_CAP_PROP_FPS); 

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo",CV_WINDOW_KEEPRATIO); //create a window called "MyVideo"
	int a = 0;
	string name;
	if( stat( "image", &info ) != 0 )
	{
		cout <<  "creating directory >>"  "image" ;
		//make a dir
		string folderName = "image";
		string folderCreateCommand = "mkdir " + folderName;
		system(folderCreateCommand.c_str());
	}
	
	
	while(1)
	{
		Mat frame;
		
		// read a new frame from video
		bool bSuccess = cap.read(frame); 

		//if not success, break loop
		if (!bSuccess) 
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		
		name = format("image/image_00%d.jpg", a);
		if(a%40)
		{
			//nothing to do
		}
		else

		{
			imwrite(name, frame);
		}

		a++;
		//show the frame in "MyVideo" window if required
		imshow("MyVideo", frame); 

		//wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		if(waitKey(30) == 27) 
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	a = 0;
	for (int a=0; a<=10000;a++)  // a <=Count would do one too many...
	{
		name = format("image/image_00%d.jpg", a);
		Mat img = imread(name); 
		//Checking successful image loading
		if ( img.empty() )      
		{
			cerr << "image file " << name << " can't be loaded!" << endl;
			continue;
		}
		imgs.push_back(img);
	}
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	//Using OpenCV Panoromic Stitiching class
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	//Saving result to hard drive
	imwrite(result_name, pano);
	//Showing result to graphical window
	imshow("MyVideo", pano);
	waitKey(0);
	//termination of program
	return 1;
}

DLLIMPORT int32_t riverLine(char pString[])
{
	Mat img = imread(pString);
	//Validating image 
	if (img.empty())
	{
		cout << "Can't read image '" << pString << "'\n";
		return -1;
	}
	Mat edges;
	//Creating Graphical Windows
	namedWindow("original",WINDOW_AUTOSIZE);
	namedWindow("result",WINDOW_AUTOSIZE);
	//Converting image to grayscale
	cvtColor(img, edges, CV_BGR2GRAY);
	//Displaying original image
	imshow("original", edges);
	GaussianBlur(edges, edges, Size(9,9), 10, 10);
	GaussianBlur(edges, edges, Size(9,9), 10, 10);
	//imshow("second", edges);//debug purpose
	Canny(edges, edges, 10, 30, 3);
	//Displaying resultant image
	imshow("result", edges);
	//Saving Result
	imwrite("result.jpg", edges);
	//if halting program is required
	//waitKey(0);
	//termination of program
	return 1;
}
