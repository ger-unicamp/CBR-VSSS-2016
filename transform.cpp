#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;
using namespace std;

int sq(int x) { return x*x; } 

//Input and Output Image;
Mat input, output;

void find_border(Point2f &p, int x, int y, int dx, int dy, const Mat &img)
{
    while(!img.at<uchar>(y,x) )
    {
    circle(input, Point(x,y), 1, (0,255,0), -1);
        printf("%d %d\n", x, y);
        x += dx, y += dy;
        if(x < 0 || x >= img.cols || y < 0 || y >= img.rows)
        {
            x = max(x, 0);
            x = min(x, img.cols - 1);

            y = max(y, 0);
            y = min(y, img.rows - 1);

            dx *= -1, dy *= -1;
        }
    }
    printf("%d\n", (int) img.at<uchar>(y,x));
    p = Point2f(x, y);
}

int main( )
{
    // Input Quadilateral or Image plane coordinates
    int threshold = 100;
    int thresholdProp = 1;
    int apertureSize = 1;
    int L2gradient = true;

    Point2f inputQuad[4]; 
    // Output Quadilateral or World plane coordinates
    Point2f outputQuad[4];
         
    // Lambda Matrix
    Mat lambda( 2, 4, CV_32FC1 );
     
    //Load the image
    input = imread( "Imagens/campo_bonito_2.png", 1 );
    // Set the lambda matrix the same type and size as input
    lambda = Mat::zeros( input.rows, input.cols, input.type() );


    Mat imagem_hsv = Mat::zeros(input.size(), CV_8UC3);
    cvtColor(input, imagem_hsv, COLOR_BGR2HSV);

    vector<Mat> channelHSV;
    split(imagem_hsv, channelHSV);

 

    Mat imagemBranco;
    inRange(imagem_hsv, Scalar(0, 0, 150), Scalar(255, 50, 230), imagemBranco);    //Display input and output


  /// Apply the erosion operation
  int erosion_size = 1;
  erode( imagemBranco, imagemBranco, getStructuringElement( MORPH_ELLIPSE,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) ) );
  erosion_size = 2;
  dilate( imagemBranco, imagemBranco, getStructuringElement( MORPH_RECT,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) ) );


    // The 4 points that select quadilateral on the input , from top-left in clockwise order
    // These four pts are the sides of the rect box used as input 

    find_border(inputQuad[0], 0, 0, -1, 1, imagemBranco);
    find_border(inputQuad[1], input.cols - 1, 0, 1, 1, imagemBranco);
    find_border(inputQuad[2], input.cols - 1, input.rows - 1, 1, -1, imagemBranco);
    find_border(inputQuad[3], 0, input.rows - 1, 1, 1, imagemBranco);

    circle(input,inputQuad[0], 5, (0,0,255), -1);
    circle(input,inputQuad[1], 5, (0,0,255), -1);
    circle(input,inputQuad[2], 5, (0,0,255), -1);
    circle(input,inputQuad[3], 5, (0,0,255), -1);

//    inputQuad[0] = Point2f( 55,25 );
//    inputQuad[1] = Point2f( input.cols-60,0);
//    inputQuad[2] = Point2f( input.cols-45,input.rows-1);
//    inputQuad[3] = Point2f( 40,input.rows-20  );

    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( input.cols-1,0);
    outputQuad[2] = Point2f( input.cols-1,input.rows-1);
    outputQuad[3] = Point2f( 0,input.rows-1  );
 
    // Get the Perspective Transform Matrix i.e. lambda 
    lambda = getPerspectiveTransform( inputQuad, outputQuad );
    // Apply the Perspective Transform just found to the src image
    warpPerspective(input,output,lambda,output.size() );

    imshow("White",imagemBranco);
    imshow("Input",input);
    imshow("Output", output);
 
    waitKey(0);
    return 0;
}
