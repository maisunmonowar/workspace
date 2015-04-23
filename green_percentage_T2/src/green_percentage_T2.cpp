//============================================================================
// Name        : Health_Estimation.cpp
// Author      : Maisun Monowar, Abdulla Kafi, Raihana Antara, Munir Maruf
// Version     : 02
// Copyright   : GPL V.2
// Description : This program analyzes video from default source and calculates
//		crop health and makes appropiate sugesstion to user.
//
//
//Online Reporsitory of this code is at github.com/maisunmonowar/workspace
//============================================================================



//including required files to compile this program
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



//Using Standard Name Space
using namespace std; 

//Using OpenCV Namespace
using namespace cv;



//Defining 'green' color in HSV color space

#define green_h_h 80
#define green_h_l 45
#define green_s_h 255
#define green_s_l 30
#define green_v_h 200
#define green_v_l 30



//Defining "Healthy Green" Color in HSV color space

#define healthy_h_h 65
#define healthy_h_l 55
#define healthy_s_h	255
#define healthy_s_l 30
#define healthy_v_h 200
#define healthy_v_l 30



//Main Function

int main(int, char**)
{
	//Initializing Variables to use in the program
	
	Mat img_hsv;
	Mat imgThresholded;
	Mat healthyThreshold;
	Mat edges;
	int total_pixel = 0;
	int total_green = 0;
	int healthy_green = 0;
	float percentage_green = 0;
	float percentage_healthy_green ;
	
	
	
	// open the default camera
    	VideoCapture cap(0); 
    	
    	
    	// check if we succeeded
    	if(!cap.isOpened())  
        	return -1;

    	//Creating windows to display results
    	namedWindow("edges",1);
	namedWindow( "Original Image", WINDOW_AUTOSIZE );
	namedWindow( "Thresholded Image", WINDOW_AUTOSIZE );
	namedWindow( "Healthy Thresholded Image", WINDOW_AUTOSIZE );

    	//Running an infinite loop to process incoming videos
    	for(;;)
    	{
        	//Create a Temporary Matrix to hols image
        	Mat image;
        	// get a new frame from camera
        	cap >> image; 
        	total_pixel = image.total();
        	//Convert image to HSV color space
        	cvtColor(image, img_hsv, COLOR_BGR2HSV);
        	//Threshholding image to display
        	inRange(img_hsv, Scalar(green_h_l, green_s_l, green_v_l), Scalar(green_h_h, green_s_h, green_v_h), imgThresholded); //Threshold the image
        	inRange(img_hsv, Scalar(healthy_h_l, healthy_s_l, healthy_v_l), Scalar(healthy_h_h, healthy_s_h, healthy_v_h), healthyThreshold);
        	
        	
        	//Following block of code is credited to
        	//http://stackoverflow.com/questions/7899108/opencv-get-pixel-channel-value-from-mat-image
        	for(int i = 0; i < img_hsv.rows; i++)
        	{
        		for(int j = 0; j < img_hsv.cols; j++)
        		{
        			Vec3b hsvPixel = img_hsv.at<Vec3b>(i, j);
        			// Compare Each pixel
        			if (hsvPixel.val[1] > green_s_l)
        			{
        				if (hsvPixel.val[2]>green_v_l && hsvPixel.val[2]<green_v_h)
        				{
        					if (hsvPixel.val[0]>green_h_l && hsvPixel.val[0]<green_h_h)
        					{
        						//this Pixel is a "Green" pixel as defined above
        						total_green++;
        						
        						
        						//Searching for "Healthy Green"
        						if (hsvPixel.val[1] > healthy_s_l)
        						{
        							if (hsvPixel.val[2]>healthy_v_l && hsvPixel.val[2]<healthy_v_h)
        							{
        								if (hsvPixel.val[0]>healthy_h_l && hsvPixel.val[0]<healthy_h_h)
        								{
        									//This Pixel is "Healthy Green"
        									healthy_green++;
        								}
        							}
        						}
        					}
        				}
        			}
        		}
        	}
        	//Pixel comparision complete
       	
       		//Calculating Percentage of Green Pixel
        	percentage_green = total_green * 100.0 / total_pixel;
        	
        	//Calculating Percentage of Healthy Green Pixel
        	percentage_healthy_green = healthy_green * 100.0/ total_green ;

        	
        	
        	//display the result on window
        	imshow( "Original Image", image );
        	imshow( "Thresholded Image", imgThresholded );
        	imshow( "Healthy Thresholded Image", healthyThreshold );
	
		//Save result as image if required 
	 	//imwrite("imgThresholded.jpg", imgThresholded);
    		//imwrite("healthyThreshold.jpg", healthyThreshold);

        	
        	
        	//state calculation data to user
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
        	
        	
        	
        	//Make a statement

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

        //break from infinite loop if user presses 'Esc' key
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    // Return an intergar
    return 1;
}
