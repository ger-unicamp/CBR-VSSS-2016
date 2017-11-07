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

    Point2i p[4];
    p[0].x = 89;
    p[0].y = 2;
    p[1].x = 597;
    p[1].y = 30;
    p[2].x = 567;
    p[2].y = 480;
    p[3].x = 55;
    p[3].y = 455;
    // P0 is the superior left corner
    // P1, P2 and P3 continue clockwise
    createTrackbar("P0-X", "Control", &p[0].x, dWidth);
    createTrackbar("P0-Y", "Control", &p[0].y, dHeight);
    createTrackbar("P1-X", "Control", &p[1].x, dWidth);
    createTrackbar("P1-Y", "Control", &p[1].y, dHeight);
    createTrackbar("P2-X", "Control", &p[2].x, dWidth);
    createTrackbar("P2-Y", "Control", &p[2].y, dHeight);
    createTrackbar("P3-X", "Control", &p[3].x, dWidth);
    createTrackbar("P3-Y", "Control", &p[3].y, dHeight);

    // Optimal values
    // P0 : (111,47) P1 : (566,10) P2 : (579, 415) P3 : (135, 421)

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        set_border_manually(frame, p[0], p[1], p[2], p[3]);

        Mat transformed_frame = transform(frame);

        circle(frame, p[0], 5, Scalar(255, 0, 0), -1);
        circle(frame, p[1], 5, Scalar(0, 255, 0), -1);
        circle(frame, p[2], 5, Scalar(0, 0, 255), -1);
        circle(frame, p[3], 5, Scalar(255, 255, 255), -1);

        imshow("MyVideo_Original", frame); //show the frame in "MyVideo" window
        imshow("MyVideo_Transformed", transformed_frame); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
                cout << "esc key is pressed by user" << endl;
                break; 
           }
    }
    return 0;

}
