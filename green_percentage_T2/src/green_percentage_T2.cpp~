//============================================================================
// Name        : green_percentage_T2.cpp
// Author      : Maisun Monowar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


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
#define healthy_s_h	255
#define healthy_s_l 30
#define healthy_v_h 200
#define healthy_v_l 30


int main(int, char**)
{
	Mat img_hsv, imgThresholded, healthyThreshold;
		int total_pixel = 0;
		int total_green = 0;
		int healthy_green = 0;
		float percentage_green = 0;
		float percentage_healthy_green ;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);

	namedWindow( "Original Image", WINDOW_AUTOSIZE );
	namedWindow( "Thresholded Image", WINDOW_AUTOSIZE );
	namedWindow( "Healthy Thresholded Image", WINDOW_AUTOSIZE );

    for(;;)
    {
        Mat image;
        cap >> image; // get a new frame from camera

        ////////////////////////////
        total_pixel = image.total();

        	cvtColor(image, img_hsv, COLOR_BGR2HSV);

        	inRange(img_hsv, Scalar(green_h_l, green_s_l, green_v_l), Scalar(green_h_h, green_s_h, green_v_h), imgThresholded); //Threshold the image
        	inRange(img_hsv, Scalar(healthy_h_l, healthy_s_l, healthy_v_l), Scalar(healthy_h_h, healthy_s_h, healthy_v_h), healthyThreshold);


        	//http://stackoverflow.com/questions/7899108/opencv-get-pixel-channel-value-from-mat-image
        	for(int i = 0; i < img_hsv.rows; i++)
        	{
        		for(int j = 0; j < img_hsv.cols; j++)
        		{
        			Vec3b hsvPixel = img_hsv.at<Vec3b>(i, j);



        			// do something with BGR values...
        			if (hsvPixel.val[1] > green_s_l)
        			{
        				if (hsvPixel.val[2]>green_v_l && hsvPixel.val[2]<green_v_h)
        				{
        					if (hsvPixel.val[0]>green_h_l && hsvPixel.val[0]<green_h_h)
        					{
        						total_green++;

        						//time to fine tune
        						if (hsvPixel.val[1] > healthy_s_l)
        						{
        							if (hsvPixel.val[2]>healthy_v_l && hsvPixel.val[2]<healthy_v_h)
        							{
        								if (hsvPixel.val[0]>healthy_h_l && hsvPixel.val[0]<healthy_h_h)
        								{
        									healthy_green++;
        								}
        							}
        						}
        					}
        				}
        			}
        		}
        	}
        	//http://stackoverflow.com/questions/7859196/read-hsv-value-of-pixel-in-opencv
        	/*
          cv::MatIterator_<cv::Vec3b> it = image.begin<cv::Vec3b>(), it_end = image.end<cv::Vec3b>();

        for(; it != it_end; ++it)
        {
        // work with pixel in here, e.g.:
        	cv::Vec3b& pixel = *it; // reference to pixel in image
        if (pixel[1] > 60)
        {
        	if (pixel[2]>30 && pixel[2]<80)
        	{
        		if (pixel[0]>45 && pixel[0]<80)
        			{
        				total_green++;

        				//time to fine tune
        				if (pixel[1] > 60)
        				{
        					if (pixel[2]>30 && pixel[2]<80)
        					{
        						if (pixel[0]>55 && pixel[0]<65)
        							{
        								healthy_green++;
        							}
        					}
        				}
        			}
        	}
        }*/
        	/*
        	 * cv::Vec3b& pixel = *it; // reference to pixel in image
        pixel[0] = 0; // changes pixel in image
        pixel[0] = 0; // H
        pixel[1] = 0; // S
        pixel[2] = 0; // V
        	 */


        	percentage_green = total_green * 100.0 / total_pixel;
        //	percentage_healthy_green= 0;
        	//percentage_healthy_green = percentage_healthy_green + 1.0;
        	percentage_healthy_green = healthy_green * 100.0/ total_green ;

        	//display graphic

        	imshow( "Original Image", image );

        	imshow( "Thresholded Image", imgThresholded );
      //  	imwrite("imgThresholded.jpg", imgThresholded);

        	imshow( "Healthy Thresholded Image", healthyThreshold );
    //    	imwrite("healthyThreshold.jpg", healthyThreshold);

        	//state calculation data
        	std::cout <<"Total Pixel ";
        	std::cout <<total_pixel;

        	std::cout <<"\nGreen Pixels ";
        	std::cout <<total_green;

        	std::cout <<"\nHealthy Pixels ";
        	std::cout <<healthy_green;

        	std::cout <<"\nGreen percentage ";
        	std::cout <<percentage_green;

        	std::cout <<"% \nHealthy green  ";
        	std::cout <<percentage_healthy_green;

        	std::cout <<"% \n ";

        	std::cout <<"\n";
        	std::cout <<"\n";

        	if((int)percentage_healthy_green < 20)
        	{
        		std::cout <<"Your farm needs expert opinion.\n\n";
        	}
        	else
        	{
        		if((int)percentage_healthy_green < 50)
        		{
        			std::cout <<"Your farm appears to be unfertilized.\n\n";
        		}
        		else
        		{
        			if((int)percentage_healthy_green < 80)
        			{
        				std::cout <<"Your farm appears to be in good shape.\n\n";
        			}
        			else
        			{
        				std::cout <<"Your farm appears to be in excellent shape.\n\n";
        			}
        		}
        	}

        /////////////////////////////
        cvtColor(image, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
