//============================================================================
// Name        : Super_Resolution.cpp
// Author      : Maisun Ibn Monowar, Abdulla Kafi, Raihana Antara, Munir Maruf
// Version     : 01
// Copyright   : GPL V.2
// Description : This program takes a video file and produces a panaroma 
// 		style super map
//
//Online	: github.com/maisunmonowar/workspace
//============================================================================



//Including files necessary to compile

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/stitching/stitcher.hpp"


//Using Standard and OpenCV namespace
using namespace std;
using namespace cv;


//Initializing Global Variables

vector<Mat> imgs;
string result_name = "result.jpg";


//main function
int main(int argc, char* argv[])
{
	struct stat info;
	
	// open the video file for reading
	VideoCapture cap(argv[1]); 
	
	// Check for valid video file
	// if not success, exit program
	if ( !cap.isOpened() )  
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//offset video file if necessary
	//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

	//get the frames per seconds of the video
	double fps = cap.get(CV_CAP_PROP_FPS); 
	cout << "Frame per seconds : " << fps << endl;
	
	//create a window called "MyVideo"
	namedWindow("MyVideo",CV_WINDOW_KEEPRATIO); 
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
	
	//Split and save video frames
	while(1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		//if not success, break loop
		if (!bSuccess) 
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		
		//Name to save file
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
	// a <=Count would do one too many...
	for (int a=0; a<=10000;a++)  
	{
		//creating a name
		name = format("image/image_00%d.jpg", a);
		Mat img = imread(name); 
		//Making sure image is loaded
		if ( img.empty() )      
		{
			cerr << "image file " << name << " can't be loaded!" << endl;
			continue;
		}
		//Load image into Structure
		imgs.push_back(img);
	}
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	//Stitching using OpenCV Library
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	//Save result
	imwrite(result_name, pano);
	//Using the Same Window to Display result
	imshow("MyVideo", pano);
	waitKey(0);
	//Program finish. Return integar
	return 1;
}
