#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    int threshold = 100;
    int thresholdProp = 1;
    int apertureSize = 1;
    int L2gradient = true;


    Mat image;
    image = imread("Imagens/campo_bonito_1.png", CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Mat imagem_hsv = Mat::zeros(image.size(), CV_8UC3);
    cvtColor(image, imagem_hsv, COLOR_BGR2HSV);

    vector<Mat> channelHSV;
    split(imagem_hsv, channelHSV);


    namedWindow( "Control", WINDOW_AUTOSIZE );
    createTrackbar("threshold", "Control", &threshold, 200);
    createTrackbar("thresholdProp", "Control", &thresholdProp, 1);
    createTrackbar("apertureSize", "Control", &apertureSize, 5);
    createTrackbar("L2gradient", "Control", &L2gradient, 1);

    namedWindow( "Display window 2", WINDOW_AUTOSIZE );// Create a window for display.
    while(1)
    {
        Mat borders = Mat::zeros(image.size(), CV_8UC3);;
        vector<vector<Point> > contours;
        contours.clear();
        vector<Vec4i> hierarchy;      
        hierarchy.clear();

        Canny(channelHSV[2], borders, threshold, threshold * (thresholdProp + 1), 2 *(apertureSize) + 1, L2gradient);

        findContours(borders, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));

        Mat imagem_contours = Mat::zeros(image.size(), CV_8UC3);

        for(int i = 0; i < contours.size(); i++)
        {
//            approxPolyDP(contours[i], contours[i], 15, true);
            drawContours(imagem_contours, contours, i, Scalar(255, 0, 0), FILLED);
        }

        imshow( "Display window 2", imagem_contours);                   // Show our image inside it.
        waitKey(0);                                          // Wait for a keystroke in the window
   }

/*    namedWindow( "Display window 0", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window 0", channelHSV[0]);                   // Show our image inside it.

    namedWindow( "Display window 1", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window 1", channelHSV[1]);                   // Show our image inside it.

    namedWindow( "Display window 2", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window 2", channelHSV[2]);                   // Show our image inside it.
*/

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
