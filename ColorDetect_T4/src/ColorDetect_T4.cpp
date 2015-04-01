//============================================================================
// Name        : ColorDetect_T4.cpp
// Author      : Maisun Monowar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;

int main( int argc, char** argv )
{
  Mat image;
  image = imread( argv[1], 1 );

  if( argc != 2 || !image.data )
    {
      std::cout <<"No image data \n" ;
      return -1;
    }

  Mat imgHSV;

     cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV


  namedWindow( "Display Image RGB", WINDOW_AUTOSIZE );
  imshow( "Display Image", image );
  namedWindow( "Display Image", WINDOW_AUTOSIZE );
    imshow( "Display Image HSV", imgHSV );
  Vec3b intensity = image.at<uchar>(25, 25);
  float vaal = intensity.val[0];
  float sat = intensity.val[1];
  float hue = intensity.val[2];

  std::cout <<"hue ";
  std::cout <<hue;

  std::cout <<"\n saturation ";
    std::cout <<sat;

    std::cout <<" \n Value ";
    std::cout <<vaal;
    std::cout <<" \n";
  waitKey(0);

  return 0;
}

