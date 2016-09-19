#include "video.hpp"
#include "videoio.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void find_border(Point2f &p, int x, int y, int dx, int dy, const Mat &img)
{
    int counter = 0;
    while(!img.at<uchar>(y,x) )
    {
        x += dx, y += dy;
        if(x < 0 || x >= img.cols || y < 0 || y >= img.rows)
        {
            x = max(x, 0);
            x = min(x, img.cols - 1);

            y = max(y, 0);
            y = min(y, img.rows - 1);

            dx *= -1, dy *= -1;
        }
        if(++counter > 100000)
            break;
    }
    p = Point2f(x, y);
}

// Lambda Matrix
Mat lambda( 2, 4, CV_32FC1 );
int achou_borda = 0;

Mat transform(Mat input)
{
    if(achou_borda < 100)
    {    
        achou_borda++;
        int threshold = 100;
        int thresholdProp = 1;
        int apertureSize = 1;
        int L2gradient = true;

        Point2f inputQuad[4]; 
        // Output Quadilateral or World plane coordinates
        Point2f outputQuad[4];
             
         
        // Set the lambda matrix the same type and size as input
        lambda = Mat::zeros( input.rows, input.cols, input.type() );


        Mat imagem_hsv = Mat::zeros(input.size(), CV_8UC3);
        cvtColor(input, imagem_hsv, COLOR_BGR2HSV);

        vector<Mat> channelHSV;
        split(imagem_hsv, channelHSV);

     

        Mat imagem_cor;
        inRange(imagem_hsv, Scalar(0, 0, 164), Scalar(190, 125, 255), imagem_cor);    //


      /// Apply the erosion operation
        int erosion_size = 1;
        erode( imagem_cor, imagem_cor, getStructuringElement( MORPH_ELLIPSE,
                                           Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                           Point( erosion_size, erosion_size ) ) );
        erosion_size = 2;
        dilate( imagem_cor, imagem_cor, getStructuringElement( MORPH_RECT,
                                           Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                           Point( erosion_size, erosion_size ) ) );


        // The 4 points that select quadilateral on the input , from top-left in clockwise order
        // These four pts are the sides of the rect box used as input 

        find_border(inputQuad[0], 0, 0, -1, 1, imagem_cor);
        find_border(inputQuad[1], input.cols - 1, 0, 1, 1, imagem_cor);
        find_border(inputQuad[2], input.cols - 1, input.rows - 1, 1, -1, imagem_cor);
        find_border(inputQuad[3], 0, input.rows - 1, 1, 1, imagem_cor);

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
    }

    Mat output;
    warpPerspective(input,output,lambda,output.size() );

    return output;
}

struct cor_range{
    int hmin, hmax, smin, smax, vmin, vmax;
    cor_range(){}
    cor_range(int x1, int x2, int x3, int x4, int x5, int x6) : hmin(x1), hmax(x2), smin(x3), smax(x4), vmin(x5), vmax(x6) {}
};


int hmin = 0, hmax = 0, smin = 0, smax = 0, vmin= 0, vmax = 0;

Mat find_color(const Mat &input, cor_range cor)
{
    Mat imagem_hsv = Mat::zeros(input.size(), CV_8UC3);
    cvtColor(input, imagem_hsv, COLOR_BGR2HSV);

    vector<Mat> channelHSV;
    split(imagem_hsv, channelHSV);

    Mat imagem_cor;
    inRange(imagem_hsv, Scalar(cor.hmin, cor.smin, cor.vmin), Scalar(cor.hmax, cor.smax, cor.vmax), imagem_cor);    //


    /// Apply the erosion operation
    int erosion_size = 1;
    erode( imagem_cor, imagem_cor, getStructuringElement( MORPH_ELLIPSE,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) ) );
    erosion_size = 2;
    dilate( imagem_cor, imagem_cor, getStructuringElement( MORPH_RECT,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) ) );

    return imagem_cor;
}

int main(int argc, char* argv[])
{	
	
    if(argc == 1) {
	cout << "Você deve passar o número da câmera como parâmetro" << endl;
	return -1;
    }
    VideoCapture cap(argv[1][0] - '0'); // Abre a camera em que o numero eh passado como argumento

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

/*    namedWindow( "Control", WINDOW_AUTOSIZE );
    createTrackbar("Hmin", "Control", &hmin, 360);
    createTrackbar("Hmax", "Control", &hmax, 360);
    createTrackbar("Smin", "Control", &smin, 255);
    createTrackbar("Smax", "Control", &smax, 255);
    createTrackbar("Vmin", "Control", &vmin, 255);
    createTrackbar("Vmax", "Control", &vmax, 255);*/
    cor_range cor_bola(5, 42, 190, 255, 245, 255);

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat cor = find_color(frame, cor_bola);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours( cor, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        /// Draw contours
        Mat drawing = Mat::zeros( cor.size(), CV_8UC3 );
        for( int i = 0; i < contours.size(); i++ )
        {
            Scalar color = Scalar( 255, 255, 255 );
            drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
        }

        if(contours.size())
        {
            Point2f centro(0,0);
            float raio;
            minEnclosingCircle(contours[0], centro, raio);
            circle(drawing, centro, 5, (255,255,255), -1);
            printf("%lf %lf\n", centro.x, centro.y);
        }
        imshow("MyVideo_Original", frame); //show the frame in "MyVideo" window
        imshow("MyVideo_Cores", cor); //show the frame in "MyVideo" window
        imshow("MyVideo_Cores", drawing); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
                cout << "esc key is pressed by user" << endl;
                break; 
           }
    }
    return 0;

}
