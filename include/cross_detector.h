//
// Created by brdaniel on 11/12/19.
//

#ifndef PROJET_OPENCV_CMAKE_CROSS_DETECTOR_H
#define PROJET_OPENCV_CMAKE_CROSS_DETECTOR_H
#include <iostream>
#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;


Point trimming(const Mat &src, Point init, bool cross, int step, int half_square_length);
Point searchCrossCenter (const Mat& src, bool top);
tuple<Point, Point> searchCross(const Mat& src);


#endif //PROJET_OPENCV_CMAKE_CROSS_DETECTOR_H
