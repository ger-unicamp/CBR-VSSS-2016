#ifndef GER_VSSS_HPP
#define GER_VSSS_HPP

#include "video.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// circle represented by its center and its radius
struct Circle{
	Point2f center;
	float radius;
	Circle(){}
	Circle(Point2f _center, float _radius) : center(_center), radius(_radius) {}
};

// color defined by minimun and maximum values of its HSV components
struct color_range{
    int hmin, hmax, smin, smax, vmin, vmax;
    color_range(){}
    color_range(int x1, int x2, int x3, int x4, int x5, int x6) : hmin(x1), hmax(x2), smin(x3), smax(x4), vmin(x5), vmax(x6) {}
};

extern const color_range ball_color;
extern const color_range blue;
extern const color_range yellow;
extern const color_range green;
extern const color_range white;
extern const color_range purple;
extern const color_range brown;

// returns a binary image created from "input" where a pixel is white if 
// the input pixel belongs to the color_range given
Mat find_color(const Mat input, color_range color);

// returns the transformed field
// the four corners are found from "input" and a new image is created
Mat transform(Mat input);

// finds contours with the requested color
// and stores the minimum enclosing circle for each contour in the res vector
void find_circles(Mat imagem, color_range color_sought, vector<Circle> &res);

// set manually the four point to transform the image
void set_border_manually(Mat input, Point2f p0, Point2f p1, Point2f p2, Point2f p3);

float point_distance(Point2f a, Point2f b);

#endif