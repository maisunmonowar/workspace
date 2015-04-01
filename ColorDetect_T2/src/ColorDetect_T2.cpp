#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat GetThresholdedImage(Mat image_here)
{
Mat image_here1=image_here;
cvtColor(image_here,image_here1,CV_BGR2HSV);
inRange(image_here1, Scalar(76, 82, 178), Scalar(97, 163, 255), image_here1);
//inRange(image_here1, Scalar(20, 100, 100), Scalar(30, 255, 255), image_here1);
return image_here1;
}



int main(int argc, char* argv[])
{
    VideoCapture cap(0); // open the video camera no. 0

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //width of frames of ideo
double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //height of frames of the video
    Mat imgtrack(dWidth,dHeight,CV_8UC3);
    imgtrack.setTo(0);

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (1)
    {
    Mat frame;

    bool bSuccess = cap.read(frame); // read a new frame from video
    //imshow("MyVideo", frame);
    if (!bSuccess) //if not success, break loop
    {
        cout << "Cannot read a frame from video stream" << endl;
        break;
    }


     Mat imgYellowThresh=GetThresholdedImage(frame);




    imshow("MyVideo", imgYellowThresh);



   cout<<endl<<"moving to imgproc";
    cout<<"end";
    if (waitKey(30) == 27)
    {
    cout << "esc key is pressed by user" << endl;
    break;
    }
}

return 0;

}
