#include "ger_vsss.hpp"
#include <math.h>

const color_range ball_color(5, 42, 190, 255, 245, 255);
const color_range blue(87, 125, 137, 255, 196, 255);
const color_range yellow(18, 51, 106, 255, 152, 255);
const color_range green(36, 87, 54, 255, 71, 255);
const color_range white(0, 190, 0, 160, 200, 255);
const color_range purple(115, 161, 85, 255, 229, 255); //ajustar os valores
const color_range brown(0, 45, 104, 199, 118, 184); //ajustar os valores
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
static int found_borders = 0;

Mat transform(Mat input)
{
    if(found_borders < 100) // after 100 iterations, considers that the field will not move
    {
        found_borders++;
 
		Point2f inputQuad[4]; // array containing the four corners of the field
		Point2f outputQuad[4]; // array containing the four corners of the image            
         
        // Set the lambda matrix the same type and size as input
        lambda = Mat::zeros( input.rows, input.cols, input.type() );

		// Gets the binary image of the white sections
        Mat white_binary_image = find_color(input, white);

        // The 4 points that select quadilateral on the input, from top-left in clockwise order
        // These four points are the sides of the rectangular box used as input 
        find_border(inputQuad[0], 0, 0, -1, 1, white_binary_image);
        find_border(inputQuad[1], input.cols - 1, 0, 1, 1, white_binary_image);
        find_border(inputQuad[2], input.cols - 1, input.rows - 1, 1, -1, white_binary_image);
        find_border(inputQuad[3], 0, input.rows - 1, 1, 1, white_binary_image);

		// If needed, set manually like this:
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
    }

    Mat output;

    // Apply the Perspective Transform just found to the src image
    warpPerspective(input,output,lambda,output.size());

    return output;
}


Mat find_color(const Mat input, color_range color)
{
	// creates an HSV image from the input
    Mat hsv_image = Mat::zeros(input.size(), CV_8UC3);
    cvtColor(input, hsv_image, COLOR_BGR2HSV);

    Mat binary_image; // filters the image to a binary image with the color requested
    inRange(hsv_image, Scalar(color.hmin, color.smin, color.vmin), Scalar(color.hmax, color.smax, color.vmax), binary_image);

    // Apply the erosion operation and then dilation. In theory, it removes small interferences from the image.
    // Increase erosion size to remove bigger "spots"
    int erosion_size = 1;
    erode( binary_image, binary_image, getStructuringElement( MORPH_ELLIPSE,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) ) );
    int dilation_size = 2;
    dilate( binary_image, binary_image, getStructuringElement( MORPH_RECT,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) ) );

    return binary_image;
}

void find_circles(Mat image, color_range color_sought, vector<Circle> &res)
{
	// Creates binary image white the selected color
    Mat binary_image = find_color(image, color_sought);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    // Finds countours and stores them in the "contours" vector
    findContours( binary_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    for(int i = 0; i < contours.size(); i++)
    {
        Point2f center(0,0);
        float radius;
        // finds the smallest possible circle that contains the contour
        minEnclosingCircle(contours[i], center, radius);

        // stores it in the output vector
        res.push_back(Circle (center, radius));
    }
}


float point_distance(Point2f a, Point2f b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

