#include "ger_vsss.hpp"

// finds one of the vertices of the field (depending on the parameters)
// used only by the transform function

void find_border(Point2f &p, int x, int y, int dx, int dy, const Mat &img)
{
    int counter = 0;
    while(!img.at<uchar>(y,x) ) // the function "at" returns true if the pixel at coordinates (y, x) is white
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
        if(++counter > 100000) // if it did not find the border, stops trying
            break;
    }
    p = Point2f(x, y); // assigns the corner found to the point given
}

static Mat lambda( 2, 4, CV_32FC1 );
static int achou_borda = 0;

Mat transform(Mat input)
{
    if(achou_borda < 100) // after 100 iterations, considers that the field will not move
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

void encontra_circulos(Mat imagem, cor_range cor_procurada, vector<circulo> &res)
{
        Mat cor = find_color(imagem, cor_procurada);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours( cor, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        /// Draw contours
//       Mat drawing = Mat::zeros( cor.size(), CV_8UC3 );
/*        for( int i = 0; i < contours.size(); i++ )
        {
            Scalar color = Scalar( 255, 255, 255 );
            drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
        }
*/
        for(int i = 0; i < contours.size(); i++)
        {
            Point2f centro(0,0);
            float raio;
            minEnclosingCircle(contours[i], centro, raio);
//            circle(drawing, centro, 5, Scalar(0,255,255), -1);

            res.push_back(circulo (centro, raio));
//            printf("%lf %lf\n", centro.x, centro.y);
        }

}

