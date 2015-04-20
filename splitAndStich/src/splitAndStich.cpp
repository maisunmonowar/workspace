//============================================================================
// Name        : splitAndStich.cpp
// Author      : Maisun Ibn Monowar
// Version     :
// Copyright   : Sample from internet
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/stitching/stitcher.hpp"
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
using namespace cv;
vector<Mat> imgs;
string result_name = "result.jpg";

int main(int argc, char* argv[])
{
	struct stat info;
	VideoCapture cap(argv[1]); // open the video file for reading

	if ( !cap.isOpened() )  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

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
					//

	}
//	else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
	    //direct
		//cout << "%s is a directory\n"   "image" ;
	//else
	//{
	//    cout <<  "%s is no directory\n"  "image" ;
	//}



	while(1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		//
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
		//
		imshow("MyVideo", frame); //show the frame in "MyVideo" window if required

		if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	a = 0;
	for (int a=0; a<=1000;a++)  // a <=Count would do one too many...
	{
		name = format("image/image_00%d.jpg", a);
		Mat img = imread(name); // pgm implies grayscale, maybe even: imread(name,0); to return CV_8U
		if ( img.empty() )      // please, *always check* resource-loading.
		{
			cerr << "image file " << name << " can't be loaded!" << endl;
			continue;
		}
		imgs.push_back(img);

	}
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	imwrite(result_name, pano);
	imshow("MyVideo", pano);
	waitKey(0);
	return 1;
}
