#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;
using namespace std;

//Input and Output Image;
Mat input, output;

int main( )
{
    // Input Quadilateral or Image plane coordinates
    int threshold = 100;
    int thresholdProp = 1;
    int apertureSize = 1;
    int L2gradient = true;

    input = imread( "Imagens/campo_bonito_1.png", 1 );

    Mat imagem_hsv = Mat::zeros(input.size(), CV_8UC3);
    cvtColor(input, imagem_hsv, COLOR_BGR2HSV);

    vector<Mat> channelHSV;
    split(imagem_hsv, channelHSV);

    int hmin = 0, hmax = 0, smin = 0, smax = 0, vmin= 0, vmax = 0;

    namedWindow( "Control", WINDOW_AUTOSIZE );
    createTrackbar("Hmin", "Control", &hmin, 360);
    createTrackbar("Hmax", "Control", &hmax, 360);
    createTrackbar("Smin", "Control", &smin, 255);
    createTrackbar("Smax", "Control", &smax, 255);
    createTrackbar("Vmin", "Control", &vmin, 255);
    createTrackbar("Vmax", "Control", &vmax, 255);
    imshow("Input",input);

    namedWindow( "Display window 2", WINDOW_AUTOSIZE );// Create a window for display.
    while(1)
    {

        Mat imagemBranco;
        inRange(imagem_hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), imagemBranco);    //


        /// Apply the erosion operation
        int erosion_size = 1;
        erode( imagemBranco, imagemBranco, getStructuringElement( MORPH_ELLIPSE,
                                           Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                           Point( erosion_size, erosion_size ) ) );
        erosion_size = 2;
        dilate( imagemBranco, imagemBranco, getStructuringElement( MORPH_RECT,
                                           Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                           Point( erosion_size, erosion_size ) ) );

        imshow( "Display window 2", imagemBranco);                   // Show our image inside it.
        waitKey(30);                                          // Wait for a keystroke in the window
   }


 



 
    waitKey(0);
    return 0;
}
