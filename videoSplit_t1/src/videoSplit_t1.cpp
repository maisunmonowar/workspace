//============================================================================
// Name        : videoSplit_t1.cpp
// Author      : Maisun Ibn Monowar
// Version     :
// Copyright   : Sample from internet
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]); // open the video file for reading

	if ( !cap.isOpened() )  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	//
	int a = 0;
	string name;

	//

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
		name = format("/home/maisun/workspace/workspace/videoSplit_t1/Debug/image/image_00%d.jpg", a);
		if(a%40)
		{
			//muri khai
		}
		else

		{
			imwrite(name, frame);
		}

		a++;
		//
		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}
