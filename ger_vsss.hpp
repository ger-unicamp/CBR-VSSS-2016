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

// returns a binary image created from "input" where a pixel is white if 
// the input pixel belongs to the color_range given
Mat find_color(const Mat &input, color_range cor);

// returns the transformed field
// the four corners are found from "input" and a new image is created
Mat transform(Mat input);

#endif