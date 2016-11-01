#include "video.hpp"
#include "videoio.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "opencv.hpp"
#include <iostream>
#include "ger_vsss.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{	
    // if did not receive expected number of arguments, prints usage instructions
    // the user must send the cam number as a parameter
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <cam number>" << endl;
        return -1;
    }


    VideoCapture cap(argv[1][0] - '0'); // opens the camera whose parameter was given

    if (!cap.isOpened())  // if not success, exits program and prints error message
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl; // prints image size


    namedWindow( "Control", WINDOW_AUTOSIZE );

    color_range color;
    createTrackbar("Hmin", "Control", &color.hmin, 255);
    createTrackbar("Hmax", "Control", &color.hmax, 255);
    createTrackbar("Smin", "Control", &color.smin, 255);
    createTrackbar("Smax", "Control", &color.smax, 255);
    createTrackbar("Vmin", "Control", &color.vmin, 255);
    createTrackbar("Vmax", "Control", &color.vmax, 255);

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat cor = find_color(frame, color);

        imshow("MyVideo_Original", frame); //show the frame in "MyVideo" window
        imshow("MyVideo_Cores", cor); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
                cout << "esc key is pressed by user" << endl;
                break; 
           }
    }
    return 0;

}
